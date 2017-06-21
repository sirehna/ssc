# Build image
#   docker build -f Dockerfile -t ssc .
#
# Delete image
#   docker rmi ssc
#
# Run container
#   docker run --name test_ssc ssc
#   docker stop test_ssc
#   docker rm test_ssc
#
# Run interactive
#   docker run -it ssc /bin/bash
#
# This Dockerfile will create an image with
#
# - gcc/g++/gfortran                                V 4.9.2
# - wget / git / ninja
# - Python3                                         V 3.4
# - /opt/cmake                                      V 3.7.2
# - /opt/HDF5                                       V 1.10.0
# - /opt/boost with its geometry extensions         V 1.60.0
# - /opt/CoinIpopt                                  V 1.7.2
# - /opt/ssc

# It builds ssc, tests it and installs it

# Require Internet to download all dependencies

FROM debian
MAINTAINER Guillaume Jacquenot <guillaume.jacquenot@sirehna.com>

# Install dependencies

# libbz2 is required for Boost compilation
RUN apt-get update -yq && apt-get install -y \
    build-essential \
    wget \
    git \
    cmake \
    ninja-build \
    python3 \
    python3-dev \
    gfortran \
    libblas3 \
    liblapack3 \
    libbz2-dev \
    pandoc \
    doxygen \
    && apt-get clean \
    && rm -rf /tmp/* /var/tmp/* \
    && rm -rf /var/lib/apt/lists/

RUN mkdir -p /opt
WORKDIR /opt

RUN mkdir -p /opt/cmake && \
    wget https://cmake.org/files/v3.7/cmake-3.7.2-Linux-x86_64.sh -O cmake.sh && \
    sh ./cmake.sh --exclude-subdir --prefix=/opt/cmake && \
    rm -rf cmake.sh
ENV PATH="/opt/cmake/bin:${PATH}"

# HDF5 with fortran support
# RUN wget https://support.hdfgroup.org/ftp/HDF5/releases/hdf5-1.8.17/src/hdf5-1.8.17.tar.gz -O hdf5_src.tar.gz
# Version hdf5-1.8.18 -> Requires CMake 3.1.0
# RUN wget https://support.hdfgroup.org/ftp/HDF5/current18/src/hdf5-1.8.18.tar.gz -O hdf5_src.tar.gz
# Version hdf5-1.10.0-patch1 -> Requires CMake 3.1.0
RUN wget https://support.hdfgroup.org/ftp/HDF5/releases/hdf5-1.10/hdf5-1.10.0-patch1/src/hdf5-1.10.0-patch1.tar.gz -O hdf5_src.tar.gz && \
    mkdir -p HDF5_SRC && \
    tar -xf hdf5_src.tar.gz --strip 1 -C HDF5_SRC && \
    mkdir -p HDF5_build && \
    cd HDF5_build && \
    cmake -G "Unix Makefiles" \
      -DCMAKE_BUILD_TYPE:STRING=Release \
      -DCMAKE_INSTALL_PREFIX:PATH=/opt/HDF5 \
      -DBUILD_SHARED_LIBS:BOOL=ON \
      -DBUILD_TESTING:BOOL=OFF \
      -DHDF5_BUILD_EXAMPLES:BOOL=OFF \
      -DHDF5_BUILD_HL_LIB:BOOL=ON \
      -DHDF5_BUILD_CPP_LIB:BOOL=ON \
      -DHDF5_BUILD_FORTRAN:BOOL=ON \
      ../HDF5_SRC && \
    make install && \
    cd .. && \
    rm -rf HDF5_build && \
    rm -rf HDF5_SRC && \
    rm -rf hdf5_src.tar.gz

# Give the user root access, go on!
RUN echo "$USER ALL = NOPASSWD: ALL" >> /etc/sudoers && \
    ##################
    # Download ipopt source
    # http://www.coin-or.org/Ipopt/documentation/node10.html
    ##################
    export IPOPT_VERSION=3.12.6 && \
    gfortran --version && \
    mkdir -p CoinIpopt_build && \
    cd CoinIpopt_build && \
    wget http://www.coin-or.org/download/source/Ipopt/Ipopt-$IPOPT_VERSION.tgz && \
    gunzip Ipopt-$IPOPT_VERSION.tgz && \
    tar -xvf Ipopt-$IPOPT_VERSION.tar && \
    rm -rf Ipopt-$IPOPT_VERSION.tar && \
    mv Ipopt-$IPOPT_VERSION CoinIpopt && \
    cd CoinIpopt && \
    # Download BLAS, LAPACK, and ASL
    cd ThirdParty/Blas && \
        ./get.Blas && \
    cd ../Lapack && \
        ./get.Lapack && \
    cd ../ASL && \
        ./get.ASL && \
    # Download MUMPS Linear Solver
    cd ../Mumps && \
        ./get.Mumps && \
    # # Download METIS
    # cd ../Metis && \
    #     ./get.Metis && \
    #############################
    # Compile ipopt statically
    #############################
    cd ../../ && \
    mkdir build && \
    cd build && \
    mkdir -p /opt/CoinIpopt && \
    ../configure -with-pic --disable-shared --prefix=/opt/CoinIpopt && \
    make && \
    make test && \
    make install && \
    rm -rf /opt/CoinIpopt_build


# BOOST 1.60 with Boost geometry extensions
# SSC : system thread random chrono
# XDYN : program_options filesystem system regex
RUN wget http://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.gz -O boost_src.tar.gz && \
    mkdir -p boost_src && \
    tar -xf boost_src.tar.gz --strip 1 -C boost_src && \
    rm -rf boost_src.tar.gz && \
    cd boost_src && \
    ./bootstrap.sh && \
    # link=shared && \
    ./b2 cxxflags=-fPIC --without-mpi --without-python link=static threading=single threading=multi --layout=tagged --prefix=/opt/boost install > boost.log 2> boost.err && \
    cd .. && \
    rm -rf boost_src && \
    # BOOST Geometry extension
    git clone https://github.com/boostorg/geometry && \
    cd geometry && \
    git checkout 4aa61e59a72b44fb3c7761066d478479d2dd63a0 && \
    cp -rf include/boost/geometry/extensions /opt/boost/include/boost/geometry/. && \
    cd .. && \
    rm -rf geometry

#RUN mkdir -p /opt/share
ADD . /opt/share/ssc

RUN mkdir -p ssc_build \
 && cd ssc_build \
 && cmake -Wno-dev \
             -G Ninja \
             -DCMAKE_INSTALL_PREFIX:PATH=/opt/ssc \
             -DIPOPT_ROOT:PATH=/opt/CoinIpopt \
             -DBOOST_ROOT:PATH=/opt/boost \
             ../share/ssc \
 && ninja \
 && ./run_all_tests --gtest_output=xml:run_all_tests.xml 

CMD cd ssc_build \
    && ninja package \
    && cp ssc*.deb /out
