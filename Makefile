.PHONY: all

all: \
	debian_10_release_gcc_8

windows_posixthreads: BUILD_TYPE=Release
windows_posixthreads: BUILD_DIR=build_win
windows_posixthreads: CPACK_GENERATOR=ZIP
windows_posixthreads: DOCKER_IMAGE=sirehna/base-image-win64-gccx-posixthreads:20210210-6e8b3c5
windows_posixthreads: BOOST_ROOT=/usr/src/mxe/usr/x86_64-w64-mingw32.static.posix
windows_posixthreads: CREATE_INDIVIDUAL_LIBRARIES=False
windows_posixthreads: ci_env=
windows_posixthreads: windows_cmake windows_build windows_test

windows_win32threads: BUILD_TYPE=Release
windows_win32threads: BUILD_DIR=build_win32threads
windows_win32threads: CPACK_GENERATOR=ZIP
windows_win32threads: DOCKER_IMAGE=sirehna/base-image-win64-gccx-win32threads
windows_win32threads: BOOST_ROOT=/usr/src/mxe/usr/x86_64-w64-mingw32.static
windows_win32threads: CREATE_INDIVIDUAL_LIBRARIES=False
windows_win32threads: ci_env=
windows_win32threads: windows_cmake windows_build windows_test

debian_9_release_gcc_6: BUILD_TYPE=Release
debian_9_release_gcc_6: BUILD_DIR=build_deb9
debian_9_release_gcc_6: CPACK_GENERATOR=DEB
debian_9_release_gcc_6: DOCKER_IMAGE=sirehna/base-image-debian9-gcc6
debian_9_release_gcc_6: BOOST_ROOT=/opt/boost
debian_9_release_gcc_6: CREATE_INDIVIDUAL_LIBRARIES=True
debian_9_release_gcc_6: ci_env=
debian_9_release_gcc_6: linux_cmake linux_build linux_test

debian_10_release_gcc_8: BUILD_TYPE=Release
debian_10_release_gcc_8: BUILD_DIR=build_deb10
debian_10_release_gcc_8: CPACK_GENERATOR=DEB
debian_10_release_gcc_8: DOCKER_IMAGE=sirehna/base-image-debian10-gcc8
debian_10_release_gcc_8: BOOST_ROOT=/opt/boost
debian_10_release_gcc_8: CREATE_INDIVIDUAL_LIBRARIES=True
debian_10_release_gcc_8: ci_env=
debian_10_release_gcc_8: linux_cmake linux_build linux_test

debian_10_debug_gcc_8: BUILD_TYPE=Debug
debian_10_debug_gcc_8: BUILD_DIR=build_deb10_debug
debian_10_debug_gcc_8: CPACK_GENERATOR=DEB
debian_10_debug_gcc_8: DOCKER_IMAGE=sirehna/base-image-debian10-gcc8
debian_10_debug_gcc_8: BOOST_ROOT=/opt/boost
debian_10_debug_gcc_8: CREATE_INDIVIDUAL_LIBRARIES=True
debian_10_debug_gcc_8: ci_env=
debian_10_debug_gcc_8: linux_cmake linux_build linux_test

debian_10_coverage_gcc_8: BUILD_TYPE=Coverage
debian_10_coverage_gcc_8: BUILD_DIR=build_deb10_coverage
debian_10_coverage_gcc_8: CPACK_GENERATOR=DEB
debian_10_coverage_gcc_8: DOCKER_IMAGE=sirehna/base-image-debian10-gcc8-xdyn
debian_10_coverage_gcc_8: BOOST_ROOT=/opt/boost
debian_10_coverage_gcc_8: CREATE_INDIVIDUAL_LIBRARIES=True
debian_10_coverage_gcc_8: ci_env=`bash <(curl -s https://codecov.io/env)`
debian_10_coverage_gcc_8: linux_cmake linux_build linux_test

debian_10_profile_gcc_8: BUILD_TYPE=Profile
debian_10_profile_gcc_8: BUILD_DIR=build_deb10_profile
debian_10_profile_gcc_8: CPACK_GENERATOR = DEB
debian_10_profile_gcc_8: DOCKER_IMAGE = sirehna/base-image-debian10-gcc8-xdyn
debian_10_profile_gcc_8: BOOST_ROOT = /opt/boost
debian_10_profile_gcc_8: CREATE_INDIVIDUAL_LIBRARIES=True
debian_10_profile_gcc_8: ci_env=
debian_10_profile_gcc_8: linux_cmake linux_build linux_test

centos_7_5_release_gcc_485: BUILD_TYPE=Profile
centos_7_5_release_gcc_485: BUILD_DIR=build_centos75
centos_7_5_release_gcc_485: CPACK_GENERATOR=ZIP
centos_7_5_release_gcc_485: DOCKER_IMAGE=sirehna/base-image-centos75-gcc485
centos_7_5_release_gcc_485: BOOST_ROOT=/opt/boost
centos_7_5_release_gcc_485: CREATE_INDIVIDUAL_LIBRARIES=True
centos_7_5_release_gcc_485: ci_env=
centos_7_5_release_gcc_485: linux_cmake linux_build linux_test

WORKING_DIRECTORY=/opt/share
DOCKER_RUN=docker run $(ci_env) \
	--rm \
	-u $(shell id -u):$(shell id -g) \
	-v $(shell pwd):${WORKING_DIRECTORY} \
	-w ${WORKING_DIRECTORY}/ssc/${BUILD_DIR} \
	${DOCKER_IMAGE}

linux_cmake:
	mkdir -p ssc/${BUILD_DIR}
	${DOCKER_RUN} \
		cmake -Wno-dev \
			-G Ninja \
			-D CREATE_INDIVIDUAL_LIBRARIES:BOOL=${CREATE_INDIVIDUAL_LIBRARIES} \
			-D CMAKE_BUILD_TYPE=${BUILD_TYPE} \
			-D CMAKE_INSTALL_PREFIX:PATH=/opt/ssc \
			-D IPOPT_ROOT:PATH=/opt/CoinIpopt \
			-D BOOST_ROOT:PATH=${BOOST_ROOT} \
			..

linux_build: linux_cmake
	${DOCKER_RUN} \
		ninja $(NB_OF_PARALLEL_BUILDS) package

linux_test:
	${DOCKER_RUN} \
		/bin/bash -c \
		"./run_all_tests &&\
		if [[ $(BUILD_TYPE) == Coverage ]];\
		then\
		echo Coverage;\
		gprof run_all_tests gmon.out > gprof_res.txt 2> gprof_res.err;\
		bash codecov_bash.sh && \
		rm codecov_bash.sh;\
		fi"

windows_cmake:
	mkdir -p ssc/${BUILD_DIR}
	mkdir -p ssc/${BUILD_DIR}/.wine
	${DOCKER_RUN} /bin/bash -c " \
		export WINEPREFIX=${WORKING_DIRECTORY}/ssc/${BUILD_DIR}/.wine \
		&& wine winecfg \
		&& cmake -Wno-dev -G Ninja \
			-D CREATE_INDIVIDUAL_LIBRARIES:BOOL=${CREATE_INDIVIDUAL_LIBRARIES} \
			-D CMAKE_BUILD_TYPE=Release \
			-D CMAKE_INSTALL_PREFIX:PATH=${WORKING_DIRECTORY} \
			-D CPACK_GENERATOR=ZIP \
			-D BOOST_ROOT:PATH=${BOOST_ROOT} \
			-D IPOPT_ROOT:PATH=/opt/CoinIpopt \
			-D COIN_BLAS:PATH=/opt/CoinIpopt/lib/libcoinblas.a \
			-D COIN_LAPACK:PATH=/opt/CoinIpopt/lib/libcoinlapack.a \
			-D COIN_MUMPS:PATH=/opt/CoinIpopt/lib/libcoinmumps.a \
			-D COIN_IPOPT:PATH=/opt/CoinIpopt/lib/libipopt.a \
			-D IPOPT_INCLUDE_DIRS:PATH=/opt/CoinIpopt/include/coin \
			-D IPOPT_LIB_DYNAMIC=\"gfortran;gcc;quadmath;m\" \
			${WORKING_DIRECTORY}/ssc"

windows_build:
	${DOCKER_RUN} /bin/bash -c " \
		export WINEPREFIX=${WORKING_DIRECTORY}/ssc/${BUILD_DIR}/.wine \
		&& wine winecfg \
		&& ninja -j1 package"

windows_test:
	${DOCKER_RUN} /bin/bash -c " \
		export WINEPREFIX=${WORKING_DIRECTORY}/ssc/${BUILD_DIR}/.wine \
		&& wine winecfg \
		&& wine ./run_all_tests --gtest_filter=-WebSocketObserverTest*"

clean:
	rm -rf ssc/build_*

lint:
	@cd ssc && \
	if grep --recursive --include={*.cpp,*.c,*.hpp,*.h,*.md,*.yml,*.cmake.*.xml,*.html,*.in,*.txt} \
	        --exclude-dir={eigen,f2c,gcovr,geographiclib,gmock,google-test,gtest,websocketpp,yaml-cpp,geometry,integrate,interpolation,rapidjson} -P "\t" . ; \
	then echo "Tabs found in the lines shown above."; false; \
	else echo "Repo passed no-tabs check."; fi && \
	cd ..
