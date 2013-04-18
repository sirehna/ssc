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
              src/random_increasing_vector.cpp)
# ------8<---------------------------------------------->8-----


set(exception_handling_dir "${CMAKE_CURRENT_BINARY_DIR}/../../exception_handling")
set(random_data_generator_dir "${CMAKE_CURRENT_BINARY_DIR}/../../random_data_generator")

find_library(exception_handling_LIBRARIES NAME ${CMAKE_STATIC_LIBRARY_PREFIX}exception_handling_static${CMAKE_STATIC_LIBRARY_SUFFIX}
             HINTS ${exception_handling_dir})
find_library(random_data_generator_LIBRARIES NAME ${CMAKE_STATIC_LIBRARY_PREFIX}random_data_generator_static${CMAKE_STATIC_LIBRARY_SUFFIX}
             HINTS ${random_data_generator_dir})
enable_testing()

# Include directories
include_directories (inc)
include_directories(SYSTEM ${GTEST_INCLUDE_DIR})
include_directories(${random_data_generator_SOURCE_DIR}/inc)

add_library (${PROJECT_NAME} OBJECT ${SRC})


ADD_DEPENDENCIES(${PROJECT_NAME} googlemock)
