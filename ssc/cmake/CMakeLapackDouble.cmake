SET(BUILD_TESTING       OFF CACHE BOOL "Lapack configuration")
SET(BUILD_SINGLE        OFF CACHE BOOL "Lapack configuration")
SET(BUILD_DOUBLE        ON  CACHE BOOL "Lapack configuration")
SET(BUILD_COMPLEX       OFF CACHE BOOL "Lapack configuration")
SET(BUILD_COMPLEX16     OFF CACHE BOOL "Lapack configuration")
SET(BLAS_SINGLE         OFF CACHE BOOL "BLAS configuration")
SET(BLAS_DOUBLE         OFF CACHE BOOL "BLAS configuration")
SET(BLAS_COMPLEX        OFF CACHE BOOL "BLAS configuration")
SET(BLAS_COMPLEX16      OFF CACHE BOOL "BLAS configuration")
SET(LAPACKE             OFF CACHE BOOL "Lapack C interface")
SET(LAPACKE_WITH_TMG    OFF CACHE BOOL "Additional library for Lapacke")
ADD_SUBDIRECTORY(lapack EXCLUDE_FROM_ALL)