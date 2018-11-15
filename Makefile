.PHONY: all tests build cmake

all: tests

tests: build
	docker run --rm -v $(shell pwd):/shared -w /shared/ssc/build ssc ./run_all_tests

build: cmake
	docker run --rm -v $(shell pwd):/shared -w /shared/ssc/build ssc ninja package \

cmake:
	docker run --rm -v $(shell pwd):/shared -w /shared/ssc/build ssc \
		cmake -Wno-dev \
			  -G Ninja \
			  -DCMAKE_BUILD_TYPE=Debug \
			  -DCMAKE_INSTALL_PREFIX:PATH=/opt/ssc \
			  -DIPOPT_ROOT:PATH=/opt/CoinIpopt \
			  -DBOOST_ROOT:PATH=/opt/boost \
			  /shared/ssc

