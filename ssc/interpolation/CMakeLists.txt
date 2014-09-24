CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)
PROJECT(interpolation)

CONFIGURE_FILE(${F2C_INCLUDE_DIR}/f2c.h
               ${CMAKE_CURRENT_BINARY_DIR}/f2c.h COPYONLY)

FILE(GLOB SRC Splines.cpp
              NaturalSplines.cpp
              ParabolicRunoutSplines.cpp
              CubicRunoutSplines.cpp
              VectorOfEquallySpacedNumbers.cpp
              LinearInterpolation.cpp
              PiecewiseConstant.cpp
              ParabolicInterpolation.cpp
              ParabolicCoefficients.cpp
              LinearInterpolationVariableStep.cpp
              ConstantStepInterpolator.cpp
              Interpolator.cpp
              SplineVariableStep.cpp
              IndexFinder.cpp
              VariableStepInterpolation.cpp
              cubspl.c
              dgtsv.c
              xerbla.c)

SET(CMAKE_C_FLAGS "")#${CMAKE_C_FLAGS} -Werror -pedantic -pedantic-errors -Wextra -Wall -Wunused-function -Wunused-label -Wunused-parameter -Wunused-value -Wunused-variable -fno-common -Wformat=2 -Winit-self -Wpacked -Wp,-D_FORTIFY_SOURCE=2 -Wpointer-arith -Wlarger-than-65500 -Wmissing-declarations -Wmissing-format-attribute -Wsign-compare -Wstrict-aliasing=2 -Wundef -ffast-math -Wconversion")
INCLUDE_DIRECTORIES(${SSC_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(SYSTEM ${CMAKE_CURRENT_BINARY_DIR})

# Using C++ 2011
# The -std=c++0x option causes g++ to go into 'strict ANSI' mode so it doesn't declare non-standard functions
# (and _stricmp() is non-standard - it's just a version of strcmp() that's case-insensitive).
# Use -std=gnu++0x instead.
IF(NOT(MSVC))
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
ENDIF()

ADD_LIBRARY(${PROJECT_NAME}_object OBJECT ${SRC})
ADD_SUBDIRECTORY(unit_tests)
