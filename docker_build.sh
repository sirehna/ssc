#!/bin/sh

docker build -f Dockerfile -t ssc .

echo "Run CMake"
docker run --rm -v $(pwd):/opt/share -w /opt/share ssc \
    cmake -Wno-dev \
          -G Ninja \
          -DCMAKE_INSTALL_PREFIX:PATH=/opt/ssc \
          -DIPOPT_ROOT:PATH=/opt/CoinIpopt \
          -DBOOST_ROOT:PATH=/opt/boost \
          /opt/share/ssc

echo "Build package"
docker run --rm -v $(pwd):/opt/share -w /opt/share ssc ninja package

echo "Run all tests"
docker run --rm -v $(pwd):/opt/share -w /opt/share ssc ./run_all_tests
