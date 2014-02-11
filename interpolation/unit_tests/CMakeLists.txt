# ------8<---[LINES TO MODIFY WHEN CHANGING MODULE]----->8-----
set(MODULE_UNDER_TEST interpolation)
project (${MODULE_UNDER_TEST}_tests)
FILE(GLOB SRC src/SplinesTest.cpp
              src/VectorOfEquallySpacedNumbersTest.cpp
              src/TwoDimensionalInterpolationTest.cpp
              src/LinearInterpolationTest.cpp
              src/PiecewiseConstantTest.cpp
              src/ParabolicInterpolationTest.cpp
              src/LinearInterpolationVariableStepTest.cpp
              src/PiecewiseConstantVariableStepTest.cpp
              src/random_increasing_vector.cpp
              src/SplineVariableStepTest.cpp
              src/IndexFinderTest.cpp)
# ------8<---------------------------------------------->8-----



# Include directories
include_directories (inc)
include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
include_directories(${random_data_generator_INCLUDE_DIRS})

add_library(${PROJECT_NAME} OBJECT ${SRC})


