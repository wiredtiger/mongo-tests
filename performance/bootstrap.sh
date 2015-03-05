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


