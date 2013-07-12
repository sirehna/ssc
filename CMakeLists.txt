cmake_minimum_required (VERSION 2.8.8)
project (matrix_and_vector_classes)

FILE(GLOB SRC src/SparseMatrix.cpp
              src/SparseVector.cpp)

include_directories(${exception_handling_INCLUDE_DIRS})
include_directories(${test_macros_INCLUDE_DIRS})
include_directories (inc)

set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/inc                                                                               CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")
add_library (${PROJECT_NAME}_static STATIC ${SRC})

add_subdirectory(unit_tests)
