cmake_minimum_required (VERSION 2.6)
project (csv_writer)

set(SRC CSVWriter.cpp)

include_directories(${SSC_INCLUDE_DIRS})

add_library (${PROJECT_NAME}_object OBJECT ${SRC})

set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/inc                                                                               CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")

add_subdirectory(unit_tests)
