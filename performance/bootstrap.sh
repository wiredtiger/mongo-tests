# clone mongodb repo
git clone https://github.com/mongodb/mongo.git
cd mongo

# update the wt merge script to use develop
sed -i.bak 's/^\(REMOTEBRANCH=\).*/\1"develop"/' ./buildscripts/update-vendor-wiredtiger
./buildscripts/update-vendor-wiredtiger

# build mongod
scons -j 20 mongod || exit $?

# download and extract the performance tests
curl -OJL https://api.github.com/repos/wiredtiger/mongo-tests/tarball/master
mkdir -p mongo-tests
TARBALL=$(echo wiredtiger-mongo-tests-*.tar.gz)
tar --strip-components 1 -C mongo-tests -zxf $TARBALL */performance

# download, extract and build YCSB
curl -OJL https://api.github.com/repos/achille/YCSB/tarball/master
mkdir -p ycsb
TARBALL=$(echo achille-YCSB-*.tar.gz)
tar --strip-components 1 -C ycsb -zxf $TARBALL 
(cd ycsb; 
 mvn package -pl mongodb -am)

# run the ycsb tests
./mongo-tests/performance/ycsb/ycsb-performance.sh 

