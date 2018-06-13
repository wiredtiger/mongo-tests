# Ensure read only testing hasn't left things difficult to cleanup.
chmod -R u+w build_posix
git reset --hard && git clean -fdqx -e '*.tgz'
cd build_posix
echo ${BUILD_NUMBER} > JENKINS_BUILD
sh reconf

../configure CC=/usr/local/gcc47/bin/gcc \
    --disable-shared \
    --enable-diagnostic --enable-strict \
    --enable-lz4 --enable-snappy --enable-zlib --enable-zstd > /dev/null
make > /dev/null
make clean > /dev/null

../configure CC=/usr/local/gcc54/bin/gcc \
    --enable-diagnostic --enable-strict \
    --enable-lz4 --enable-snappy --enable-zlib --enable-zstd > /dev/null
make > /dev/null
make clean > /dev/null

../configure CC=/usr/local/gcc63/bin/gcc \
    --enable-diagnostic --enable-strict \
    --enable-lz4 --enable-snappy --enable-zlib --enable-zstd > /dev/null
make > /dev/null
make clean > /dev/null

../configure CC=/usr/local/gcc71/bin/gcc \
    --enable-diagnostic --enable-strict \
    --enable-lz4 --enable-snappy --enable-zlib --enable-zstd > /dev/null
make > /dev/null
make clean > /dev/null

../configure CC=/usr/local/gcc81/bin/gcc \
    --enable-diagnostic --enable-strict \
    --enable-lz4 --enable-snappy --enable-zlib --enable-zstd > /dev/null
make > /dev/null
make clean > /dev/null

# default clang on the test machines is 3.4
../configure CC=/usr/bin/clang \
    --enable-diagnostic --enable-strict \
    --enable-lz4 --enable-snappy --enable-zlib --enable-zstd > /dev/null
make > /dev/null
make clean > /dev/null

../configure CC=/usr/local/clang40/bin/clang \
    --enable-diagnostic --enable-strict \
    --enable-lz4 --enable-snappy --enable-zlib --enable-zstd > /dev/null
make > /dev/null
make clean > /dev/null

PATH=/usr/local/clang50/bin:$PATH ../configure CC=clang LD=clang \
    --enable-diagnostic --enable-strict \
    --enable-lz4 --enable-snappy --enable-zlib --enable-zstd > /dev/null
make > /dev/null
make clean > /dev/null

if [ "$ghprbTargetBranch" == "mongodb-3.0" ]; then
    echo "Cannot run remaining check against mongodb-3.0"
    exit 0
fi

if [ "$ghprbTargetBranch" == "mongodb-3.2" ]; then
    echo "Cannot run remaining check against mongodb-3.2"
    exit 0
fi

../configure  CPPFLAGS="-fvisibility=hidden" CC=/usr/local/gcc63/bin/gcc \
    --enable-diagnostic --enable-strict \
    --enable-lz4 --enable-snappy --enable-zlib --enable-zstd > /dev/null
make > /dev/null
make clean > /dev/null
