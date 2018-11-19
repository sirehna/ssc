.PHONY: all tests build cmake

all: tests

tests: build
	docker run --rm -v $(shell pwd):/shared -w /shared/ssc/build ssc ./run_all_tests

build: cmake
	docker run --rm -v $(shell pwd):/shared -w /shared/ssc/build ssc ninja package

cmake:
	docker run --rm -v $(shell pwd):/shared -w /shared/ssc/build ssc \
        cmake -Wno-dev \
              -G Ninja \
              -DCMAKE_BUILD_TYPE=Debug \
              -DCMAKE_INSTALL_PREFIX:PATH=/opt/ssc \
              -DIPOPT_ROOT:PATH=/opt/CoinIpopt \
              -DBOOST_ROOT:PATH=/opt/boost \
              /shared/ssc

windows:
	docker run --rm -u $( shell id -u $USER ):$( shell id -g $USER ) \
        -v $(shell pwd):/opt/share \
        -w /opt/share mydockcross/windows-x64 \
        /bin/bash -c "mkdir /opt/share/.wine && \
                      export WINEPREFIX=/opt/share/.wine && \
                      wine winecfg && \
                      cmake -Wno-dev -G Ninja \
                        -DCMAKE_BUILD_TYPE=Release \
                        -DCMAKE_INSTALL_PREFIX:PATH=/opt/ssc \
                        -DCPACK_GENERATOR=ZIP \
                        -DIPOPT_ROOT:PATH=/opt/CoinIpopt \
                        -DBOOST_ROOT:PATH=/opt/boost \
                        -DBOOST_INCLUDEDIR:PATH=/opt/boost/include \
                        -DBoost_INCLUDE_DIR:PATH=/opt/boost/include \
                        -DBOOST_LIBRARYDIR:PATH=/opt/boost/lib \
                        -DBoost_NO_SYSTEM_PATHS:BOOL=OFF \
                        -DBoost_LIBRARY_DIR_RELEASE:PATH=/opt/boost/lib \
                        -DBoost_DEBUG=1 \
                        -DCOIN_BLAS:PATH=/opt/CoinIpopt/lib/libcoinblas.a \
                        -DCOIN_LAPACK:PATH=/opt/CoinIpopt/lib/libcoinlapack.a \
                        -DCOIN_MUMPS:PATH=/opt/CoinIpopt/lib/libcoinmumps.a \
                        -DCOIN_IPOPT:PATH=/opt/CoinIpopt/lib/libipopt.a \
                        -DIPOPT_INCLUDE_DIRS:PATH=/opt/CoinIpopt/include/coin \
                        -DIPOPT_LIB_DYNAMIC=\"gfortran;gcc;quadmath;m\" \
                      /opt/share/ssc"
	docker run --rm -u $( shell id -u $USER ):$( shell id -g $USER ) \
        -v $(shell pwd):/opt/share \
        -w /opt/share mydockcross/windows-x64 \
        /bin/bash -c "mkdir -p /opt/share/.wine && \
                      export WINEPREFIX=/opt/share/.wine && \
                      wine winecfg && \
                      ninja package"
	docker run --rm -u $( shell id -u $USER ):$( shell id -g $USER ) \
        -v $(shell pwd):/opt/share \
        -w /opt/share mydockcross/windows-x64 \
        /bin/bash -c "mkdir -p /opt/share/.wine && \
                      export WINEPREFIX=/opt/share/.wine && \
                      wine winecfg && \
                      wine ./run_all_tests --gtest_filter=-WebSocketObserverTest*"

