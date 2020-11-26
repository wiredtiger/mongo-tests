#include <cstdint>
#include <iostream>
#include <vector>
#include <ctime>
#include <thread>
#include <random>
#include <unistd.h>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/pool.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

/* MONGOD CONNECTION */
// Setup default mongodb connection and pool
mongocxx::instance instance{};
mongocxx::pool pool{mongocxx::uri{}};


/* SETTINGS */
int doc_count = 1000; // Num docs per collection

// Num find and modify threads, note that each collection has an insert thread associated with it.
int thread_count = 10;
int collection_count = 1; // Num collections (currently can only be 1)

// Time between min_id start and max_id start, the oldest document should be 120 seconds older
// than the newest doc
int alive_duration_secs = 120;

// How old a document should be when it is added to the expired document list.
int expire_duration_secs = 60;

// The interval between each document in milliseconds, i.e. if we have X docs across a window of
// alive_duration_secs how many milliseconds is between each doc?
int doc_interval_millis = (alive_duration_secs * 1000) / doc_count;

// The value that will be inserted into the document, and will get replaced by each find and modify.
int value_size_bytes = 100000;


/* VOLATILES */
// Track global min and max document id's currently doesn't allow for multiple collections.
volatile int min_id = 0;
volatile int max_id = doc_count;

// Track the application status.
volatile bool running = true;


/* RANDOM GENERATORS */
// Setup a pretty basic probability distribution skewing
// heavily towards the start of the range
std::mt19937 gen;
double interval[] = {0,   0.05, 0.1,   0.2,   1};
double weights[] =  {0.8, 0.15, 0.025, 0.025, 0};

// Create a global piecewise linear distribution, seems to work fine with multithreading.
std::piecewise_linear_distribution<> id_distribution(std::begin(interval),
                                                std::end(interval),
                                                std::begin(weights));


// Function to generate a random string to populate our values.
std::string gen_random_string(const int len) {
    std::string tmp_s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::uniform_int_distribution<> distrib(0, sizeof(alphanum) - 2);
    tmp_s.reserve(len);
    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[distrib(gen)];
    return tmp_s;
}

// Get the next record id to find and modify, this uses the piecewise linear distribution to skew
// to the start of the range.
static int get_next_record_id(){
    double random = id_distribution(gen);
    return std::floor(random * (max_id - min_id)) + min_id;
}

// The insertion thread, this thread also updates the min_id.
void insert(mongocxx::client &c, std::string coll_name) {
    mongocxx::collection coll = c["mydb"][coll_name];
    auto last_run = std::chrono::system_clock::now();
    int id_check = 0;
    while (running) {
        bool inserted = false;
        // Loop until we've successfully inserted one doc.
        do {
            bsoncxx::document::value doc_value = document{} << "date"
            <<  bsoncxx::types::b_date(last_run)
            << "x" << gen_random_string(value_size_bytes)
            << "id" << max_id << finalize;
            auto result = coll.insert_one(doc_value.view());
            if (result) {
                inserted = true;
            }
        } while (!inserted);
        max_id++;

        // Every 10 runs update our minimum record id, log it for clarity.
        if (id_check % 10 == 0) {
            auto doc_result = coll.find_one({});
            if (doc_result) {
                bsoncxx::document::value doc = *doc_result;
                auto id = doc.view()["id"].get_int32();
                if (min_id < id) {
                    min_id = id;
                }
            }
            std::cout << "Min id: " << min_id << "Max id: " << max_id << std::endl;
            id_check = 0;
        }

        // Loop until we need to insert our next document. If our insertion or id check takes longer
        // than doc_interval_millis we'll gradually decrease our document set. This could be fixed
        // but is a bit complicated.
        auto next_time = std::chrono::system_clock::now();
        while (next_time - last_run < std::chrono::milliseconds(doc_interval_millis)) {
            next_time = std::chrono::system_clock::now();
        }
        last_run = next_time;
        id_check++;
    }
}

// The function that replaces each documents "x" field with a slightly modified version, unclear if
// actually do need to modify it for the reproducer to work or if we could just insert the same.
void find_and_modify(mongocxx::client &c, std::string coll_name){
    mongocxx::collection coll = c["mydb"][coll_name];
    while (running) {
        int id = get_next_record_id();
        auto next_time = std::chrono::system_clock::now() - std::chrono::seconds(expire_duration_secs);
        bsoncxx::stdx::optional<bsoncxx::document::value> result = coll.find_one_and_update(
            document{} << "date" << open_document << "$lte" << bsoncxx::types::b_date(next_time) << close_document << finalize,
            document{} << "$set" << open_document
                    << "x" << gen_random_string(value_size_bytes) << close_document << finalize);
    }
}

// Some c++ weirdness that I haven't figured out yet. Results in having a 2 functions per thread.
void find_and_modify_func(std::string coll_name){
    auto c = pool.acquire();
    find_and_modify(*c, coll_name);
}

void insert_func(std::string coll_name){
    auto c = pool.acquire();
    insert(*c, coll_name);
}

int main(int argc, char * argv[]){
    // Make sure thread_count is divisible by collection count so each collection has an equal
    // number of threads operating on it, currently not meaningful as only 1 collection allowed due
    // to concurrency issues.
    if (thread_count % collection_count != 0) {
        return 1;
    }
    // Setup the test in this function creating the database, and populating it with an initial set
    // of documents.
    mongocxx::client client{mongocxx::uri{}};
    mongocxx::database db = client["mydb"];
    // Create doc_count documents across collection_count collections and create a ttl index on all
    // of them, Make each doc doc_interval_millis older than the previous.
    std::vector<std::string> coll_names{};

    auto start = std::chrono::system_clock::now();
    std::cout << "Beginning insert phase..." << std::endl;
    for (int i = 0; i < collection_count; i ++){
        std::string db_name = "test" + std::to_string(i);
        coll_names.push_back(db_name);
        mongocxx::collection coll = db[db_name];
        std::vector<bsoncxx::document::value> documents;
        auto new_time = start;
        for (int j = 0; j < doc_count; j ++) {
            new_time = new_time + std::chrono::milliseconds(doc_interval_millis);
            // Our document looks like this {"date" : "DATETIME", "x" : "JUNK", "id", "ID"}
            // we must have a datetime in it for TTL indexes to work, the id is to make find and
            // modify easy. The big value is our generic data, designed to give the storage engine
            // some work to do.
            bsoncxx::document::value doc_value = document{} << "date"
                <<  bsoncxx::types::b_date(new_time)
                << "x" << gen_random_string(value_size_bytes)
                << "id" << j << finalize;
            documents.push_back(doc_value);
        }
        coll.insert_many(documents);
    }
    std::cout << "Finished insert phase..." << std::endl;

    // Create TTL indexes per collection. We may want to create an "id" index to prevent collection
    // scans for each find and modify.
    mongocxx::options::index index_options{};
    index_options.expire_after(std::chrono::seconds(expire_duration_secs));
    for (auto coll_name : coll_names){
        auto index_specification = document{} << "date" << 1 << finalize;
        db[coll_name].create_index(std::move(index_specification), index_options);
        index_specification = document{} << "id" << 1 << finalize;
        db[coll_name].create_index(std::move(index_specification));
    }
    std::cout << "Created TTL indexes..." << std::endl;

    // Create the find and modify threads and insertion threads.
    std::vector<std::thread> threads{};
    for (int i = 0; i < thread_count; i ++){
        int col_id = std::floor(i / (double)(thread_count / collection_count));
        std::thread t(find_and_modify_func, coll_names[col_id]);
        threads.push_back(std::move(t));
    }
    for (auto coll_name: coll_names){
        std::thread t(insert_func, coll_name);
        threads.push_back(std::move(t));
    }
    std::cout << "Created and started all threads..." << std::endl;

    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    }
}