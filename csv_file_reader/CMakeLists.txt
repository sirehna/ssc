cmake_minimum_required (VERSION 2.6)
project (csv_file_reader)

set(SRC src/CSVFileReader.cpp)

include_directories(${exception_handling_INCLUDE_DIRS})
include_directories (inc)

add_library (${PROJECT_NAME}_static OBJECT ${SRC})


set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/inc                                                                               CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")

add_subdirectory(unit_tests)