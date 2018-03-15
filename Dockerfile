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

FROM debian:8
MAINTAINER Guillaume Jacquenot <guillaume.jacquenot@sirehna.com>

# Install dependencies

# libbz2 is required for Boost compilation
RUN apt-get update -yq && apt-get install -y \
    build-essential \
    g++-4.9 \
    gcc-4.9 \
    wget \
    git \
    ninja-build \
    python3 \
    python3-dev \
    gfortran \
    libblas3 \
    liblapack3 \
    libbz2-dev \
    pandoc \
    doxygen \
    python3-pip \
    unzip \
    && apt-get clean \
    && rm -rf /tmp/* /var/tmp/* \
    && rm -rf /var/lib/apt/lists/

RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.9 100
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 100
RUN update-alternatives --set g++ /usr/bin/g++-4.9
RUN update-alternatives --set gcc /usr/bin/gcc-4.*

RUN mkdir -p /opt
WORKDIR /opt

RUN mkdir -p /opt/cmake && \
    wget https://cmake.org/files/v3.5/cmake-3.5.2-Linux-x86_64.sh -O cmake.sh && \
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



# BOOST 1.60 with Boost geometry extensions
# SSC : system thread random chrono
# XDYN : program_options filesystem system regex
RUN wget http://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.gz -O boost_src.tar.gz && \
    mkdir -p boost_src && \
    tar -xf boost_src.tar.gz --strip 1 -C boost_src && \
    rm -rf boost_src.tar.gz
RUN cd boost_src && \
    ./bootstrap.sh && \
      link=shared
RUN cd boost_src && \
    ./b2 cxxflags=-fPIC --without-mpi --without-python link=static threading=single threading=multi --layout=tagged --prefix=/opt/boost install #> boost.log 2> boost.err
#    # BOOST Geometry extension
RUN git clone https://github.com/boostorg/geometry && \
    cd geometry && \
    git checkout 4aa61e59a72b44fb3c7761066d478479d2dd63a0 && \
    cp -rf include/boost/geometry/extensions /opt/boost/include/boost/geometry/. && \
    cd .. && \
    rm -rf geometry


##################
# Download & compile IPOPT
##################
ADD fetch_gitlab_artifacts.sh fetch_gitlab_artifacts.py /
RUN pip3 install python-gitlab==1.1.0 python-dateutil
RUn python3 /fetch_gitlab_artifacts.py --project_id 56 --target_branch with-third-parties --build_stage=run \
 && unzip artifacts.zip && rm artifacts.zip && rm -rf install
RUN mkdir -p CoinIpopt_build/build \
 && mkdir -p /opt/CoinIpopt
RUN cd CoinIpopt_build \
 && mv ../ipopt-with-third-party.tgz . \
 && tar xzf ipopt-with-third-party.tgz  \
 && rm -rf ipopt-with-third-party.tgz
RUN cd CoinIpopt_build/build \
 && .././configure -with-pic --disable-shared --prefix=/opt/CoinIpopt \
 && make \
 && make test \
 && make install \
 && rm -rf /opt/CoinIpopt_build
