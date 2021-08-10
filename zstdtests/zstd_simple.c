#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <sched.h>
#include <sys/time.h>
#include "zstd.h"
#include "common.h"

#define MIN(a,b) (((a)<(b))?(a):(b))

struct ZSTD_Context;
typedef struct ZSTD_Context ZSTD_CONTEXT;
struct ZSTD_Context {
    void *ctx; /* Either a compression context or a decompression context. */
    ZSTD_CONTEXT *next;
};

typedef enum { CONTEXT_TYPE_COMPRESS, CONTEXT_TYPE_DECOMPRESS } CONTEXT_TYPE;

int startThread = 0;
int compressionLevel;
int nParts;
int nThreads;
int thread_count = 0;
size_t chunkSize;
size_t fileSize;

size_t *compressedSizes;
void **uncompressedParts;
void **compressedParts;
void **prevCompressed;
void **decompressedParts;

pthread_mutex_t  rsrc_lock;
pthread_cond_t  rsrc_cond;

void allocateFileBuffer(void **ptr, int l, size_t chunkSize) {
    for (int i = 0; i < l; i++)
        ptr[i] = malloc(chunkSize);
}

void freeFileBuffer(void **ptr, int l) {
    for (int i = 0; i < l; i++)
        free(ptr[i]);
}

void *compressMultiZstdCCtx(void *arg) {
    int threadId = *((int *)arg);

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
        compressedSizes[j] = ZSTD_compress( compressedParts[j], 
                                        chunkSize,
                                        uncompressedParts[j], 
                                        MIN(chunkSize, fileSize - j * chunkSize),
                                        compressionLevel);
    }
}

int compressZstd(const char *fileName, const char *outFileName, int nParts, size_t chunkSize, size_t compressedSizes[]) {

    FILE *input = fopen(fileName, "rb");
    size_t bytesRead = 0;
    struct timespec start_time, end_time, elapsed_time;
    float elapsed;

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
    allocateFileBuffer(compressedParts, nParts, chunkSize);
    
    pthread_t tids[nThreads];

    for (int i = 0; i < nThreads; i++) {
        int *threadId;
        threadId = malloc(sizeof(int));
        *threadId = i;
        pthread_create(&tids[i], NULL, compressMultiZstdCCtx, threadId);
    }

    printf("Starting Zstd Compression\n");

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
    
    printf("Zstd Compression time in nano secs : %.9ld\n", elapsed_time.tv_nsec); 
    printf("Zstd Compression time in milli secs : %.4ld\n", (elapsed_time.tv_nsec / 1000000)); 

    /*
     * Write all compressed parts into one file.
     */
    remove(outFileName);
    FILE *output = fopen(outFileName, "ab+");
    fseek(output, 0, SEEK_SET);
    size_t bytesWritten = 0;
    for (int i = 0; i < nParts; i++) {
        bytesWritten += fwrite(compressedParts[i], 1, compressedSizes[i], output);
    }
    fclose(output);

    freeFileBuffer(uncompressedParts, nParts);
    freeFileBuffer(compressedParts, nParts);

    return 0;
}

int decompressZstd(const char *fileName, const char *outFileName, size_t nParts, size_t chunkSize, size_t compressedSizes[]) {
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

    for (int j = 0; j < nParts; j = j + nThreads) {
        /* 
         * If file size is not evenly divisible by desired chunk size, 
         * the last slot of file will be less than chunk size, hence take min.
         */
        ZSTD_decompress(decompressedParts[j], chunkSize, prevCompressed[j], compressedSizes[j]);
    } 
    printf("ZSTD decompression completed.\n");
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
        printf("Usage: %s nThreads inputFile outputFile zstdCompressionLevel[optional]\n", exeName);

    nThreads = atoi(argv[1]);
    const char *fname = argv[2];
    const char *outFname = argv[3];

    if (argc == 5)
        compressionLevel = atoi(argv[4]);
    else
        compressionLevel = 1; /* Default compression level */

    /* 
     * We need an array to hold size of compressed file portions for decompression.
     */
    chunkSize = 128 * 1024;
    fileSize = fsize_orDie(fname);
    nParts = fileSize / chunkSize + 1;
    uncompressedParts = malloc(sizeof(void *) * nParts);
    compressedParts = malloc(sizeof(void *) * nParts);
    compressedSizes = malloc(sizeof(size_t) * nParts);
    decompressedParts = malloc(sizeof(void *) * nParts);
    
    pthread_cond_init(&rsrc_cond, NULL);
    pthread_mutex_init(&rsrc_lock, NULL);
    compressZstd(fname, outFname, nParts, chunkSize, compressedSizes);

    /* Decompress can only be run after compress, as it requires the results of compressedSizes. */
    decompressZstd(outFname, "contextthreadsdecompressed", nParts, chunkSize, compressedSizes);

    totalTime = clock() - totalTime;
    double totalTimeTaken = ((double)totalTime)/CLOCKS_PER_SEC;
    printf("Total time taken: %f seconds.\n", totalTimeTaken);

    pthread_mutex_destroy(&rsrc_lock);
    pthread_cond_destroy(&rsrc_cond);
    return(0);
}
