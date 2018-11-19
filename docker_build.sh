#!/bin/sh

docker build -t ssc .

mkdir -p ssc/build

echo "Run CMake"
docker run --rm -v $(pwd):/shared -w /shared/ssc/build ssc \
    cmake -Wno-dev \
          -G Ninja \
          -DCMAKE_INSTALL_PREFIX:PATH=/opt/ssc \
          -DIPOPT_ROOT:PATH=/opt/CoinIpopt \
          -DBOOST_ROOT:PATH=/opt/boost \
          /shared/ssc \
&& echo "Build package" \
&& docker run --rm -v $(pwd):/shared -w /shared/ssc/build ssc ninja package \
&& echo "Run all tests" \
&& docker run --rm -v $(pwd):/shared -w /shared/ssc/build ssc ./run_all_tests
