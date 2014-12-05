Producer consumer test
======================

Producer(s) generate documents without "worker" field set, but limit the total count to 10000.
Consumer(s) query for documents without worker field set, update the field and then delete the document.

Running
-------

There are seperate scripts for running producers/consumers, consumer script deletes the database, so start it first. Each script configures the respective counts.

    mongo 16296_consumers.js
    mongo 16296_producers.js


