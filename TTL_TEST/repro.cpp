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
int doc_count = 20000; // Num docs per collection

// Number find and modify threads
int update_thread_count = 20;
// Number of reader threads
int read_thread_count = 10;
int collection_count = 1; // Num collections (currently can only be 1)

// The size of the value that will be inserted into the document, and will get replaced by each
// update operation.
int value_size_bytes = 100000;

// The value itself which is copied and then modified prior to update.
std::string big_val;

// The range of documents to update for each update thread. They'll do a sequence updates starting
// at a random key and then sequently updating the next doc_update_range keys.
int doc_update_range = 300;

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
double weights[] =  {0.2, 0.2, 0.2, 0.2, 0.2};

// Create a global piecewise linear distribution, seems to work fine with multithreading.
std::piecewise_linear_distribution<> id_distribution(std::begin(interval),
                                                std::end(interval),
                                                std::begin(weights));

std::uniform_int_distribution<> replacement_distribution(0, sizeof(value_size_bytes));

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

// The read thread, this thread tries to randomly read one value every 20 milliseconds
void read_txn(mongocxx::client &c, std::string coll_name) {
    mongocxx::collection coll = c["mydb"][coll_name];
    mongocxx::read_concern snapshot{};
    snapshot.acknowledge_level(mongocxx::read_concern::level::k_snapshot);
    auto session = c.start_session();
    while (running) {
        int id = get_next_record_id();
        mongocxx::options::transaction opts;
        opts.read_concern(snapshot);
        mongocxx::client_session::with_transaction_cb callback =
            [&](mongocxx::client_session* session) {
            coll.find_one(document{} << "id"
            << id << finalize);
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        };
        session.with_transaction(callback, opts);
    }
}

// The insertion thread, this thread also updates the min_id.
/*
void insert(mongocxx::client &c, std::string coll_name) {
    mongocxx::collection coll = c["mydb"][coll_name];
    auto last_run = std::chrono::system_clock::now();
    std::uniform_int_distribution<> distrib(0, doc_interval_millis);
    mongocxx::read_concern snapshot{};
    snapshot.acknowledge_level(mongocxx::read_concern::level::k_snapshot);
    int id_check = 0;
    auto session = c.start_session();
    while (running) {
        bool inserted = false;*/
        /*do {
            bsoncxx::document::value doc_value = document{} << "date"
            <<  bsoncxx::types::b_date(last_run)
            << "x" << big_val
            << "id" << max_id << finalize;
            auto result = coll.insert_one(doc_value.view());
            if (result) {
                inserted = true;
            }
        } while (!inserted);
        max_id++;*/
        /*std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}*/

// The find and modify thread that replaces each documents "x" field with a slightly modified
// version every 20 milliseconds.
void find_and_modify(mongocxx::client &c, std::string coll_name){
    mongocxx::collection coll = c["mydb"][coll_name];
    while (running) {
        int id = get_next_record_id();
        if (id > max_id - doc_update_range) {
            id -= doc_update_range;
        }
        for (int i = 0; i < doc_update_range; ++i){
        std::string next_val = big_val;
        next_val[replacement_distribution(gen)] = gen_random_string(1)[0];
        bsoncxx::stdx::optional<bsoncxx::document::value> result = coll.find_one_and_update(
            document{} << "id" << id << finalize,
            document{} << "$set" << open_document
                    << "x" << next_val << close_document << finalize);
            id++;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

// Some c++ weirdness that I haven't figured out yet. Results in having a 2 functions per thread.
void find_and_modify_func(std::string coll_name){
    auto c = pool.acquire();
    find_and_modify(*c, coll_name);
}

void read_func(std::string coll_name){
    auto c = pool.acquire();
    read_txn(*c, coll_name);
}

/*
void insert_func(std::string coll_name){
    auto c = pool.acquire();
    insert(*c, coll_name);
}*/

int main(int argc, char * argv[]){
    // Make sure thread_count is divisible by collection count so each collection has an equal
    // number of threads operating on it, currently not meaningful as only 1 collection allowed due
    // to concurrency issues.
    if (update_thread_count % collection_count != 0) {
        return 1;
    }
    // Setup the test in this function creating the database, and populating it with an initial set
    // of documents.
    mongocxx::client client{mongocxx::uri{}};
    mongocxx::database db = client["mydb"];
    // Create doc_count documents across collection_count collections and create a ttl index on all
    // of them, Make each doc doc_interval_millis older than the previous.
    std::vector<std::string> coll_names{};

    big_val = gen_random_string(value_size_bytes);
    std::cout << "Beginning insert phase..." << std::endl;
    for (int i = 0; i < collection_count; i ++){
        std::string db_name = "test" + std::to_string(i);
        coll_names.push_back(db_name);
        mongocxx::collection coll = db[db_name];
        std::vector<bsoncxx::document::value> documents;
        for (int j = 0; j < doc_count; j ++) {
            // Our document looks like this {"x" : "big_val", "id", "ID"}
            bsoncxx::document::value doc_value = document{} << "x" << big_val
                << "id" << j << finalize;
            documents.push_back(doc_value);
        }
        coll.insert_many(documents);
    }
    std::cout << "Finished insert phase..." << std::endl;

    // Create the find and modify threads.
    std::vector<std::thread> threads{};
    for (int i = 0; i < update_thread_count; i ++){
        int col_id = std::floor(i / (double)(update_thread_count / collection_count));
        std::thread t(find_and_modify_func, coll_names[col_id]);
        threads.push_back(std::move(t));
    }

    // Create the read threads.
    for (int i = 0; i < read_thread_count; i ++){
        int col_id = std::floor(i / (double)(read_thread_count / collection_count));
        std::thread t1(read_func, coll_names[col_id]);
        threads.push_back(std::move(t1));
    }

    std::cout << "Created and started all threads..." << std::endl;

    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    }
}