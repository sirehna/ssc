# - Find IPOPT
#
# Will define:
#
# IPOPT - the IPOPT static library
# IPOPT_INCLUDE_DIR - IPOPT's include directory
#
# Uses:
#
# IPOPT_ROOT - directory containing


find_library(
    COIN_BLAS
    libcoinblas.a
    PATHS
    ${IPOPT_ROOT}/lib
)

find_library(
    COIN_LAPACK
    libcoinlapack.a
    PATHS
    ${IPOPT_ROOT}/lib
)

find_library(
    COIN_MUMPS
    libcoinmumps.a
    PATHS
    ${IPOPT_ROOT}/lib
)

find_library(
    COIN_IPOPT
    libipopt.a
    PATHS
    ${IPOPT_ROOT}/lib
)

find_path (
          IPOPT_INCLUDE_DIRS
          IpTNLP.hpp
          PATHS ${IPOPT_ROOT}/include/coin)

if (WIN32)
    set(IPOPT ${COIN_IPOPT} ${COIN_MUMPS} ${COIN_LAPACK}
            ${COIN_BLAS}
            gfortran
            gcc_s
            m
    )
    set(IPOPT_LIB_STATIC ${COIN_IPOPT} ${COIN_MUMPS} ${COIN_LAPACK} ${COIN_BLAS})
    set(IPOPT_LIB_DYNAMIC gfortran gcc_s m) # quadmath
else()
    set(IPOPT ${COIN_IPOPT} ${COIN_MUMPS} ${COIN_LAPACK}
            ${COIN_BLAS}
            gfortran
            gcc_s
            m
            dl
    )
    set(IPOPT_LIB_STATIC ${COIN_IPOPT} ${COIN_MUMPS} ${COIN_LAPACK} ${COIN_BLAS})
    set(IPOPT_LIB_DYNAMIC gfortran gcc_s m dl) # quadmath
endif()

MESSAGE(STATUS "COIN_BLAS           : ${COIN_BLAS}")
MESSAGE(STATUS "COIN_LAPACK         : ${COIN_LAPACK}")
MESSAGE(STATUS "COIN_MUMPS          : ${COIN_MUMPS}")
MESSAGE(STATUS "COIN_IPOPT          : ${COIN_IPOPT}")
MESSAGE(STATUS "IPOPT               : ${IPOPT}")
MESSAGE(STATUS "IPOPT_LIB_DYNAMIC   : ${IPOPT_LIB_DYNAMIC}")
MESSAGE(STATUS "IPOPT_LIB_STATIC    : ${IPOPT_LIB_STATIC}")
MESSAGE(STATUS "IPOPT_INCLUDE_DIRS  : ${IPOPT_INCLUDE_DIRS}")

