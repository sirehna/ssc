cmake_minimum_required (VERSION 2.6)
project (random_data_generator)

set(SRC src/DataGenerator.cpp
        src/sir_rand.c)

set_source_files_properties(src/sir_rand.c PROPERTIES LANGUAGE CXX ) # Force the use of a C++ compiler on sir_rand.c (doesn't link otherwise)

include_directories(inc)

add_library (${PROJECT_NAME}_object OBJECT ${SRC})
add_library(${PROJECT_NAME}_static STATIC ${SRC})

set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/inc   CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")

add_subdirectory(unit_tests)

