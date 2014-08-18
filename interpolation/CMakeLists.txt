cmake_minimum_required (VERSION 2.8.8)
project(interpolation C)

FILE(GLOB SRC src/Splines.cpp
              src/NaturalSplines.cpp
              src/ParabolicRunoutSplines.cpp
              src/CubicRunoutSplines.cpp
              src/VectorOfEquallySpacedNumbers.cpp
              src/LinearInterpolation.cpp
              src/RAO.cpp
              src/PiecewiseConstant.cpp
              src/ParabolicInterpolation.cpp
              src/ParabolicCoefficients.cpp
              src/LinearInterpolationVariableStep.cpp
              src/ConstantStepInterpolator.cpp
              src/Interpolator.cpp
              src/SplineVariableStep.cpp
              src/IndexFinder.cpp
              src/VariableStepInterpolation.cpp
              src/cubspl.c)
SET(CMAKE_C_FLAGS "")#${CMAKE_C_FLAGS} -Werror -pedantic -pedantic-errors -Wextra -Wall -Wunused-function -Wunused-label -Wunused-parameter -Wunused-value -Wunused-variable -fno-common -Wformat=2 -Winit-self -Wpacked -Wp,-D_FORTIFY_SOURCE=2 -Wpointer-arith -Wlarger-than-65500 -Wmissing-declarations -Wmissing-format-attribute -Wsign-compare -Wstrict-aliasing=2 -Wundef -ffast-math -Wconversion")
include_directories(${exception_handling_INCLUDE_DIRS})
include_directories(${test_macros_INCLUDE_DIRS})
include_directories (inc)

# Using C++ 2011
# The -std=c++0x option causes g++ to go into 'strict ANSI' mode so it doesn't declare non-standard functions
# (and _stricmp() is non-standard - it's just a version of strcmp() that's case-insensitive).
# Use -std=gnu++0x instead.
IF (NOT(MSVC))
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
ENDIF()

set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/inc  CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")
add_library (${PROJECT_NAME}_object OBJECT ${SRC})
add_subdirectory(unit_tests)
