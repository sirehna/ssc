cmake_minimum_required (VERSION 2.6)
project (csv_file_reader)

set(SRC CSVFileReader.cpp)

include_directories(${SSC_INCLUDE_DIRS})

add_library (${PROJECT_NAME}_object OBJECT ${SRC})

add_subdirectory(unit_tests)