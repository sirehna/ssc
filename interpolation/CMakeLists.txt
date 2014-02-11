cmake_minimum_required (VERSION 2.8.8)
project (interpolation)

enable_language (Fortran)
set (CMAKE_Fortran_FLAGS_RELEASE "-funroll-all-loops -fno-f2c -O3 -m32 -g3 -pedantic -pedantic-errors -w -Wno-globals -Wunused -Wuninitialized -Wall -Wsurprising -Werror -W")
set (CMAKE_Fortran_FLAGS_DEBUG   "-fno-f2c -O0 -g3 -m32 -pedantic -pedantic-errors -pedantic -w -Wno-globals -Wunused -Wuninitialized -Wall -Wsurprising -Werror -W")

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
              src/cubspl.f)

include_directories(${exception_handling_INCLUDE_DIRS})
include_directories(${test_macros_INCLUDE_DIRS})
include_directories (inc)

# Using C++ 2011
# The -std=c++0x option causes g++ to go into 'strict ANSI' mode so it doesn't declare non-standard functions
# (and _stricmp() is non-standard - it's just a version of strcmp() that's case-insensitive).
# Use -std=gnu++0x instead.
ADD_DEFINITIONS("-std=gnu++0x")

set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/inc  CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")
add_library (${PROJECT_NAME}_object OBJECT ${SRC})
add_subdirectory(unit_tests)
