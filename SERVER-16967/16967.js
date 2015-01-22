(function() {
    'use strict';

    load('../lib/parallelTester.js');

    var drop = function() {
        var t = db.getSiblingDB('server16967_drop').testcoll;
        t.drop();
        for (var i=0; i<100; i++) {
            t.save({a: 1});
            t.drop();
        }
    };

    var dropThread = new ScopedThread(drop);
    dropThread.start();

    var t = db.server16967;
    t.drop();
    t.save({a: 1});
    for (var i=0; i<10; i++) {
       t.runCommand('compact');
    }

    dropThread.join(t);
}());
