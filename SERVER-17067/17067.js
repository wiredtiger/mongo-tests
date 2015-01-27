var thread=100
var testTime=100

var shortFieldNames =
  ["aa", "ba", "ca", "da", "ea", "fa", "ga", "ha", "ia", "ja",
   "ka", "la", "ma", "na", "oa", "pa", "qa", "ra", "sa", "ta",
   "ua", "va", "wa", "xa", "ya", "za", "ab", "bb", "cb", "db",
   "ri", "si", "ti", "ui", "vi", "wi", "xi", "yi", "zi", "aj",
   "xm", "ym", "zm", "an", "bn", "cn", "dn", "en", "fn", "gn"];

// var coll = db.createCollection("IncFewSmallDoc");

for (var i=0; i<100; i++) {
    var toInsert = {_id: i};
    for (var j = 0; j < 20; j++) {
        toInsert[shortFieldNames[j]] = 1;
    }
    db.IncFewSmallDoc.insert(toInsert);
}
db.IncFewSmallDoc.getDB().getLastError();

var ops = [
                  { op:  "update",
		    ns:  "test.IncFewSmallDoc",
                    query: { _id : { "#SEQ_INT" :
                                { seq_id: 0, start: 0, step: 1, mod: 100 } } },
                    update: { $inc : { aa : 1,
                                       da : 1,
                                       ha : 1,
                                       ma : 1,
                                       ta : 1 } } }
              ];

res = benchRun({ops:ops, seconds:testTime, writeCmd: true, parallel: thread});
