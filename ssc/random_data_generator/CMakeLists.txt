cmake_minimum_required (VERSION 2.6)
project (random_data_generator)

set(SRC DataGenerator.cpp
        sir_rand.c)

set_source_files_properties(sir_rand.c PROPERTIES LANGUAGE CXX ) # Force the use of a C++ compiler on sir_rand.c (doesn't link otherwise)

include_directories(${SSC_INCLUDE_DIRS})

add_library(${PROJECT_NAME}_object OBJECT ${SRC})

add_subdirectory(unit_tests)

