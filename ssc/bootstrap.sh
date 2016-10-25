#!/usr/bin/env bash

# Default Debian URL is buggy when using Vagrant or Docker from France:
# Error reading from server. Remote end closed connection [IP: 128.31.9.66 80]
sudo sed -i 's|httpredir.debian.org|ftp.debian.org|g' /etc/apt/sources.list

# Update package list
sudo apt-get update

# LCOV
sudo apt-get install lcov -y

# G++
sudo apt-get install g++ -y

# GDB
sudo apt-get install gdb -y

# DOXYGEN
sudo apt-get install doxygen -y

# GFORTRAN
sudo apt-get install gfortran -y

# CMAKE
sudo apt-get install cmake -y

# NINJA
sudo apt-get install ninja-build -y

# GIT
sudo apt-get install git -y

# PANDOC
sudo apt-get install pandoc -y
sudo apt-get install unzip -y

# SUBVERSION
sudo apt-get install subversion -y

# BOOST 1.60
# svn co http://svn.boost.org/svn/boost/tags/release/Boost_1_60_0
BOOST_INSTALL=/usr/local/boost_1_60_0 install
wget http://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.gz
tar -xf boost_1_60_0.tar.gz
cd boost_1_60_0
./bootstrap.sh
# link=shared
sudo ./b2 cxxflags=-fPIC link=static threading=single threading=multi --layout=tagged --prefix=${BOOST_INSTALL}
# BOOST Geometry extension
git clone https://github.com/boostorg/geometry
cd geometry/
git checkout 4aa61e59a72b44fb3c7761066d478479d2dd63a0
sudo cp -rf include/boost/geometry/extensions /usr/local/boost_1_60_0/include/boost/geometry/.
cd ..

srcDirectory=ssc

# GMOCK
cd /vagrant/${srcDirectory}
sudo rm -rf googletest
git clone https://github.com/google/googletest.git googletest
cd googletest
git checkout release-1.8.0
cd ..
sudo chown -R vagrant googletest
sudo chgrp -R vagrant googletest

# EIGEN
cd /vagrant/${srcDirectory}
wget http://bitbucket.org/eigen/eigen/get/3.2.10.tar.bz2 -O eigen.tar.bz2
sudo rm -rf eigen
mkdir eigen
cd eigen
tar xjf ../eigen.tar.bz2 --strip 1
sudo chown -R vagrant eigen
sudo chgrp -R vagrant eigen

# EIGEN3-HDF5
cd /vagrant/${srcDirectory}
sudo rm -rf eigen3-hdf5
git clone https://github.com/garrison/eigen3-hdf5
sudo chown -R vagrant eigen3-hdf5
sudo chgrp -R vagrant eigen3-hdf5

# GEOGRAPHICLIB
# cd /vagrant/${srcDirectory}
# rm -rf geographiclib.tgz
# wget https://sourceforge.net/projects/geographiclib/files/distrib/GeographicLib-1.30.tar.gz/download -O geographiclib.tgz
# rm -rf geographiclib
# mkdir -p geographiclib
# cd geographiclib
# tar -xf ../geographiclib.tgz --strip 1
cd /vagrant/${srcDirectory}
rm -rf geographiclib.tgz
rm -rf geographiclib
git clone http://git.code.sf.net/p/geographiclib/code geographiclib
cd geographiclib
git checkout v1.30
# Specific patch for SSC
echo "IF(CMAKE_SIZEOF_VOID_P EQUAL 8) # If on a 64 bit machine" >> src/CMakeLists.txt
echo "    IF(UNIX AND NOT WIN32) # If on Linux" >> src/CMakeLists.txt
echo "        SET(CMAKE_C_FLAGS \"\${CMAKE_C_FLAGS} -fPIC\")" >> src/CMakeLists.txt
echo "        SET(CMAKE_CXX_FLAGS \"\${CMAKE_CXX_FLAGS} -fPIC\")" >> src/CMakeLists.txt
echo "        SET(CMAKE_Fortran_FLAGS \"\${CMAKE_Fortran_FLAGS} -fPIC\")" >> src/CMakeLists.txt
echo "    ENDIF()" >> src/CMakeLists.txt
echo "ENDIF()" >> src/CMakeLists.txt
echo "add_library (Geographic_object OBJECT \${SOURCES} \${HEADERS})" >> src/CMakeLists.txt
cd ..
sudo chown -R vagrant geographiclib
sudo chgrp -R vagrant geographiclib

# YAML-CPP
cd /vagrant/${srcDirectory}
sudo rm -rf yaml-cpp
git clone https://github.com/jbeder/yaml-cpp.git
cd yaml-cpp
git checkout tags/release-0.3.0
cd ..
sudo chown -R vagrant yaml-cpp
sudo chgrp -R vagrant yaml-cpp
cp CMakeLists_yaml_cpp.txt yaml-cpp/CMakeLists.txt

# WEBSOCKETPP
cd /vagrant/${srcDirectory}
sudo rm -rf websocketpp
git clone https://github.com/zaphoyd/websocketpp
cd websocketpp
git checkout 0.7.0
cd ..

# F2C
cd /vagrant/${srcDirectory}
wget http://www.netlib.org/f2c/libf2c.zip
sudo rm -rf f2c
mkdir f2c
cd f2c
unzip ../libf2c.zip
sed 's/typedef long int integer/typedef int integer/g' f2c.h0 > f2c.h
cp signal1.h0 signal1.h
cp sysdep1.h0 sysdep1.h
cd ..
sudo chown -R vagrant yaml-cpp
sudo chgrp -R vagrant yaml-cpp
cp CMakeLists_f2c.txt f2c/CMakeLists.txt

# GCOVR
cd /vagrant/${srcDirectory}
sudo rm -rf gcovr
git clone https://github.com/gcovr/gcovr.git
cd gcovr
git checkout tags/3.2
cd ..
sudo chown -R vagrant gcovr
sudo chgrp -R vagrant gcovr

# HDF5
cd ~
wget https://www.hdfgroup.org/ftp/HDF5/releases/hdf5-1.8.12/src/hdf5-1.8.12.tar.gz -O hdf5_source.tar.gz
mkdir -p hdf5_source
tar -xf hdf5_source.tar.gz --strip 1 -C ./hdf5_source
mkdir hdf5_build
cd hdf5_build
cmake \
-Wno-dev \
../hdf5_source \
"-DBUILD_SHARED_LIBS:BOOL=OFF" \
"-DCMAKE_BUILD_TYPE:STRING=Release" \
"-DHDF5_BUILD_HL_LIB:BOOL=ON" \
"-DHDF5_BUILD_FORTRAN:BOOL=ON" \
"-DHDF5_ENABLE_F2003:BOOL=ON" \
"-DHDF5_BUILD_CPP_LIB:BOOL=ON" \
"-DHDF5_BUILD_TOOLS:BOOL=ON" \
"-DCMAKE_INSTALL_PREFIX:PATH=/usr/local/hdf5" \
"-DCMAKE_C_FLAGS=-fpic" \
"-DCMAKE_CXX_FLAGS=-fpic"
sudo make install

# IPOPT
cd ~
IPOPT_VERSION=3.12.6
IPOPT_DIRECTORY=Ipopt-${IPOPT_VERSION}
wget http://www.coin-or.org/download/source/Ipopt/Ipopt-${IPOPT_VERSION}.tgz
tar -xf Ipopt-${IPOPT_VERSION}.tgz
cd ${IPOPT_DIRECTORY}
cd ThirdParty/Blas
./get.Blas
cd ../Lapack
./get.Lapack
cd ../Mumps
./get.Mumps
cd ../../..
tar -czf Ipopt-${IPOPT_VERSION}_SRC.tgz Ipopt-${IPOPT_VERSION}

IPOPT_VERSION_UNDERSCORE=`echo ${IPOPT_VERSION} | sed 's/\./_/g'`
IPOPT_INSTALL=/usr/local/Ipopt_${IPOPT_VERSION_UNDERSCORE}
echo "Configuring, compiling, and installing Ipopt for ${IPOPT_VERSION}"
echo "Ipopt will be installed in :\"${IPOPT_INSTALL}\""
IPOPT_SRC=Ipopt-${IPOPT_VERSION}
IPOPT_BUILD=Ipopt-${IPOPT_VERSION}_build
tar -xf Ipopt-${IPOPT_VERSION}_SRC.tgz

mkdir -p ${IPOPT_BUILD}
mkdir -p ${IPOPT_INSTALL}
cd ${IPOPT_BUILD}

if [[ `uname -s` == "Linux" && `uname -m` == "x86_64" ]]
then
    echo "64 bits adding -fPIC options"
    ../${IPOPT_SRC}/configure --prefix=${IPOPT_INSTALL} --disable-shared ADD_CFLAGS="-fPIC -fexceptions" ADD_CXXFLAGS="-fPIC -fexceptions" ADD_FFLAGS="-fPIC -fexceptions"
else
    ../${IPOPT_SRC}/configure --prefix=${IPOPT_INSTALL} --disable-shared # LDFLAGS="-lpthread"
fi
make
sudo make install
cd ..

# FIRST BUILD
cd /vagrant/${srcDirectory}
mkdir build_vagrant
cd build_vagrant
cmake .. -DCMAKE_BUILD_TYPE=Release -Wno-dev -DBOOST_ROOT=${BOOST_INSTALL} -DIPOPT_ROOT=${IPOPT_INSTALL} -G Ninja
ninja
./run_all_tests
ninja package

