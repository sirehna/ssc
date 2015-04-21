cmake_minimum_required (VERSION 2.8.8)
project (matrix_and_vector_classes)

FILE(GLOB SRC src/SparseMatrix.cpp
              src/SparseVector.cpp)

include_directories (inc)
INCLUDE_DIRECTORIES(${SSC_INCLUDE_DIRS})

ADD_LIBRARY(${PROJECT_NAME}_object OBJECT ${SRC})

add_subdirectory(unit_tests)
