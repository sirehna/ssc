.PHONY: all build cmake package tests

all: package

tests: build
	docker run \
		--rm \
		-v $(shell pwd):/shared \
		-u $(shell id -u):$(shell id -g) \
		-w /shared/ssc/build_debian \
		ssc ./run_all_tests

package: tests
	docker run \
		--rm \
		-v $(shell pwd):/shared \
		-u $(shell id -u):$(shell id -g) \
		-w /shared/ssc/build_debian \
		ssc ninja package

build: cmake
	docker run \
		--rm \
		-v $(shell pwd):/shared \
		-u $(shell id -u):$(shell id -g) \
		-w /shared/ssc/build_debian \
		ssc ninja run_all_tests

cmake:
	mkdir -p ssc/build_debian
	docker build -t ssc .
	docker run \
		--rm \
		-v $(shell pwd):/shared \
		-u $(shell id -u):$(shell id -g) \
		-w /shared/ssc/build_debian \
		ssc \
		cmake -Wno-dev \
			  -G Ninja \
			  -DCMAKE_BUILD_TYPE=Debug \
			  -DCMAKE_INSTALL_PREFIX:PATH=/opt/ssc \
			  -DIPOPT_ROOT:PATH=/opt/CoinIpopt \
			  -DBOOST_ROOT:PATH=/opt/boost \
			  /shared/ssc

windows:
	docker build -t mydockcross/windows-x64 dockcross/windows_x64
	mkdir -p ssc/build_windows
	docker run \
		--rm \
		-u $(shell id -u ):$(shell id -g ) \
		-v $(shell pwd):/opt/share\
		-w /opt/share\
		mydockcross/windows-x64\
		/bin/bash -c "cd /opt/share/ssc/build_windows \
		           && mkdir -p /opt/share/ssc/build_windows/.wine \
		           && export WINEPREFIX=/opt/share/ssc/build_windows/.wine \
		           && wine winecfg \
		           && cmake -Wno-dev -G Ninja \
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
	docker run \
		--rm \
		-u $(shell id -u ):$(shell id -g )\
		-v $(shell pwd):/opt/share\
		-w /opt/share\
		mydockcross/windows-x64\
		/bin/bash -c "cd /opt/share/ssc/build_windows \
		           && mkdir -p /opt/share/ssc/build_windows/.wine \
		           && export WINEPREFIX=/opt/share/ssc/build_windows/.wine \
		           && wine winecfg \
		           && ninja package"
	docker run \
		--rm \
		-u $(shell id -u ):$(shell id -g )\
		-v $(shell pwd):/opt/share\
		-w /opt/share\
		mydockcross/windows-x64\
		/bin/bash -c "cd /opt/share/ssc/build_windows \
		           && mkdir -p /opt/share/ssc/build_windows/.wine \
		           && export WINEPREFIX=/opt/share/ssc/build_windows/.wine \
		           && wine winecfg \
		           && wine ./run_all_tests --gtest_filter=-WebSocketObserverTest*"
