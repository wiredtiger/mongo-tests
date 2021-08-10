#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>

#include "common.h"
#include "snappy-c.h"

#define MIN(a,b) (((a)<(b))?(a):(b))

int startThread = 0;
int nParts;
int nThreads;
int thread_count = 0;
size_t chunkSize;
size_t snappyChunkSize;
size_t fileSize;

size_t *compressedSizes;
size_t *snappyUncompressedSizes;
void **uncompressedParts;
void **compressedParts;
void **prevCompressed;
void **decompressedParts;

pthread_mutex_t rsrc_lock;
pthread_cond_t rsrc_cond;

void allocateFileBuffer(void **ptr, int l, size_t chunkSize) {
    for (int i = 0; i < l; i++)
        ptr[i] = malloc(chunkSize);
}

void freeFileBuffer(void **ptr, int l) {
    for (int i = 0; i < l; i++)
        free(ptr[i]);
}

void *compressMultiSnappy(void *arg) {
    int threadId = *((int *)arg);
    int snappy_status;

    if (startThread == 0) {                                                                         
        pthread_mutex_lock(&rsrc_lock);                                                             
        thread_count++;                                                                             
        pthread_cond_wait(&rsrc_cond, &rsrc_lock);                                                  
        pthread_mutex_unlock(&rsrc_lock);                                                           
    }                                                                                               
              


    for (int j = threadId; j < nParts; j = j + nThreads) {
        /* 
         * If file size is not evenly divisible by desired chunk size, 
         * the last slot of file will be less than chunk size, hence take min.
         */
        snappy_status = snappy_compress((char *)uncompressedParts[j], 
                                        MIN(chunkSize, fileSize - j * chunkSize), 
                                        (char *)compressedParts[j], 
                                        &compressedSizes[j]);

        //printf("Snappy Status: %d, Snappy Compressed Size: %ld\n", snappy_status, compressedSizes[j]);
    }
}

int compressSnappy(const char *fileName, const char *outFileName, int nParts, size_t chunkSize, size_t compressedSizes[]) {
    FILE *input = fopen(fileName, "rb");
    size_t bytesRead = 0;
    struct timespec start_time, end_time, elapsed_time;

    allocateFileBuffer(uncompressedParts, nParts, chunkSize);

    /*
     * Split file into desired chunk sizes.
     */
    for (int i = 0; i < nParts; i++) {
        bytesRead += fread_orDie(uncompressedParts[i], chunkSize, input);
    }
    fclose(input);

    /*
     * Compress each chunk and store separately.
     */
    allocateFileBuffer(compressedParts, nParts, snappyChunkSize);

    pthread_t tids[nThreads];                                                                       
                                                                                                    
    for (int i = 0; i < nThreads; i++) {                                                            
        int *threadId;                                                                              
        threadId = malloc(sizeof(int));                                                             
        *threadId = i;                                                                              
        pthread_create(&tids[i], NULL, compressMultiSnappy, threadId);                              
    }                                                                                               
                                                                                                    
    printf("Starting Snappy Compression\n");                                                        
                                                                                                    
    while (thread_count != nThreads)                                                                
            sched_yield();                                                                          
    pthread_mutex_lock(&rsrc_lock);                                                                 
    pthread_cond_broadcast(&rsrc_cond);                                                             
    pthread_mutex_unlock(&rsrc_lock);                                                               
    clock_gettime(CLOCK_REALTIME, &start_time);                                                     
    startThread = 1;                                                                                
                                                                                                    
    for (int i = 0; i < nThreads; i++)                                                              
        (void)pthread_join(tids[i], NULL);                                                          
                                                                                                    
    clock_gettime(CLOCK_REALTIME, &end_time);                                                       
    elapsed_time.tv_sec = (int)(end_time.tv_sec - start_time.tv_sec);                               
    elapsed_time.tv_nsec = end_time.tv_nsec - start_time.tv_nsec;                                   
    elapsed_time.tv_nsec = elapsed_time.tv_nsec + (elapsed_time.tv_sec * 1000000000);               
                                                                                                    
    printf("Snappy Compression time in nano secs : %.9ld\n", elapsed_time.tv_nsec);                 
    printf("Snappy Compression time in milli secs : %.4ld\n", (elapsed_time.tv_nsec / 1000000));                 
                                                                                      

    /*
     * Write all compressed parts into one file.
     */
    remove(outFileName);
    FILE *output = fopen(outFileName, "ab+");
    fseek(output, 0, SEEK_SET);
    size_t bytesWritten = 0;
    for (int i = 0; i < nParts; i++) {
        bytesWritten += fwrite(compressedParts[i], 1, compressedSizes[i], output);
        /* Required by snappy uncompress. */
        snappy_uncompressed_length(compressedParts[i], compressedSizes[i], &snappyUncompressedSizes[i]);
    }
    fclose(output);

    freeFileBuffer(uncompressedParts, nParts);
    freeFileBuffer(compressedParts, nParts);

    return 0;
}

void *decompressMultiSnappy(void *arg) {
    int threadId = *((int *)arg);

    while (startThread == 0) {
        sched_yield();
    }

    for (int j = threadId; j < nParts; j = j + nThreads) {
        /* 
         * If file size is not evenly divisible by desired chunk size, 
         * the last slot of file will be less than chunk size, hence take min.
         */
        snappy_uncompress(prevCompressed[j], compressedSizes[j], decompressedParts[j], &snappyUncompressedSizes[j]);
    } 
}

int decompressSnappy(const char *fileName, const char *outFileName, size_t nParts, size_t chunkSize, size_t compressedSizes[]) {
    prevCompressed = malloc(sizeof(void *) * nParts);
    allocateFileBuffer(prevCompressed, nParts, chunkSize);

    /*
     * Read file into memory according to compressed size of each chunk.
     */
    FILE *cf = fopen(fileName, "rb");
    size_t bytesRead = 0;
    for (int i = 0; i < nParts; i++) {
        bytesRead += fread_orDie(prevCompressed[i], compressedSizes[i], cf);
    }

    allocateFileBuffer(decompressedParts, nParts, chunkSize);

    pthread_t tids[nThreads];
    for (int i = 0; i < nThreads; i++) {
        int *threadId;
        threadId = malloc(sizeof(int));
        *threadId = i;

        pthread_create(&tids[i], NULL, decompressMultiSnappy, threadId);
    }

    startThread = 1;
    for (int i = 0; i < nThreads; i++)
        (void)pthread_join(tids[i], NULL);

    printf("Snappy decompression completed.\n");
    remove(outFileName);
    FILE *df = fopen(outFileName, "ab+");
    size_t bytesWritten = 0;
    for (int i = 0; i < nParts; i++) {
        bytesWritten += fwrite(decompressedParts[i], 1, MIN(chunkSize, fileSize - i * chunkSize), df);
    }
    fclose(df);

    freeFileBuffer(prevCompressed, nParts);
    freeFileBuffer(decompressedParts, nParts);

    return 0;
}

int main(int argc, const char **argv) {

    clock_t totalTime = clock();
    const char* const exeName = argv[0];
    if (argc < 4)
        printf("Usage: %s nThreads inputFile outputFile\n", exeName);

    nThreads = atoi(argv[1]);
    const char *fname = argv[2];
    const char *outFname = argv[3];

    /* 
     * We need an array to hold size of compressed file portions for decompression.
     */
    chunkSize = 128 * 1024;
    fileSize = fsize_orDie(fname);
    nParts = fileSize / chunkSize + 1;
    uncompressedParts = malloc(sizeof(void *) * nParts);
    snappyUncompressedSizes = malloc(sizeof(size_t) * nParts);
    compressedParts = malloc(sizeof(void *) * nParts);
    compressedSizes = malloc(sizeof(size_t) * nParts);
    decompressedParts = malloc(sizeof(void *) * nParts);
    
    snappyChunkSize = snappy_max_compressed_length(chunkSize);
    /*
        * The snappy compress algorithm requires compressed sizes to be initialized
        * to the maximum worst case size.
        */
    for (int i = 0; i < nParts; i++)
        compressedSizes[i] = snappyChunkSize;
    compressSnappy(fname, outFname, nParts, chunkSize, compressedSizes);
    /* Decompress can only be run after compress, as it requires the results of compressedSizes. */
    decompressSnappy(outFname, "snappydecompressed", nParts, chunkSize, compressedSizes);

    totalTime = clock() - totalTime;
    double totalTimeTaken = ((double)totalTime)/CLOCKS_PER_SEC;
    printf("Total time taken: %f seconds.\n", totalTimeTaken);

    pthread_mutex_destroy(&rsrc_lock);
    pthread_cond_destroy(&rsrc_cond);

    return(0);
}
