FROM debian:8
MAINTAINER Guillaume Jacquenot <guillaume.jacquenot@sirehna.com>

# Install dependencies

# libbz2 is required for Boost compilation
RUN apt-get update -yq && apt-get install -y \
        build-essential \
        doxygen \
        g++-4.9 \
        gcc-4.9 \
        gfortran-4.9 \
        git \
        libblas3 \
        liblapack3 \
        libbz2-dev \
        ninja-build \
        pandoc \
        python3 \
        python3-dev \
        python3-pip \
        unzip \
        wget \
    && apt-get clean \
    && rm -rf /tmp/* /var/tmp/* \
    && rm -rf /var/lib/apt/lists/

RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.9 100 && \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 100 && \
    update-alternatives --install /usr/bin/gfortran gfortran /usr/bin/gfortran-4.9 100 && \
    update-alternatives --set g++ /usr/bin/g++-4.9 && \
    update-alternatives --set gcc /usr/bin/gcc-4.* && \
    update-alternatives --set gfortran /usr/bin/gfortran-4.*

RUN mkdir -p /opt
WORKDIR /opt

RUN mkdir -p /opt/cmake && \
    wget https://cmake.org/files/v3.18/cmake-3.18.3-Linux-x86_64.sh -O cmake.sh && \
    sh ./cmake.sh --exclude-subdir --prefix=/opt/cmake && \
    rm -rf cmake.sh
ENV PATH="/opt/cmake/bin:${PATH}"

# HDF5 with fortran support - No HDF5 V1.10 that does not work with eigen3-hdf5
RUN wget https://support.hdfgroup.org/ftp/HDF5/current18/src/hdf5-1.8.21.tar.gz -O hdf5_src.tar.gz && \
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

# BOOST 1.60 with Boost geometry extensions
# SSC : system thread random chrono
# XDYN : program_options filesystem system regex
# libbz2 is required for Boost compilation
RUN wget http://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.gz -O boost_src.tar.gz && \
    mkdir -p boost_src && \
    tar -xzf boost_src.tar.gz --strip 1 -C boost_src && \
    rm -rf boost_src.tar.gz && \
    cd boost_src && \
    ./bootstrap.sh && \
    ./b2 cxxflags=-fPIC --without-mpi --without-python link=static threading=single threading=multi --layout=tagged --prefix=/opt/boost install && \
    cd .. && \
    rm -rf boost_src

# BOOST Geometry extension
RUN git clone https://github.com/boostorg/geometry && \
    cd geometry && \
    git checkout 4aa61e59a72b44fb3c7761066d478479d2dd63a0 && \
    cp -rf include/boost/geometry/extensions /opt/boost/include/boost/geometry/. && \
    cd .. && \
    rm -rf geometry

# Ipopt
# http://www.coin-or.org/Ipopt/documentation/node10.html
ENV IPOPT_VERSION=3.12.9
RUN gfortran --version && \
    wget http://www.coin-or.org/download/source/Ipopt/Ipopt-$IPOPT_VERSION.tgz -O ipopt_src.tgz && \
    mkdir -p ipopt_src && \
    tar -xf ipopt_src.tgz --strip 1 -C ipopt_src && \
    rm -rf ipopt_src.tgz && \
    cd ipopt_src && \
    cd ThirdParty/Blas && \
        ./get.Blas && \
    cd ../Lapack && \
        ./get.Lapack && \
    cd ../Mumps && \
        ./get.Mumps && \
    cd ../../ && \
    mkdir build && \
    cd build && \
    ../configure -with-pic --disable-shared --prefix=/opt/CoinIpopt && \
    make && \
    make test && \
    make install && \
    cd .. && \
    cd .. && \
    rm -rf ipopt_src
