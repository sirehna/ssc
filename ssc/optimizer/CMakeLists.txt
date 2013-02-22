cmake_minimum_required (VERSION 2.6)
project (optimizer)
set(SOURCES src/OptimizationProblem.cpp)

include_directories(inc)
include_directories(${test_macros_SOURCE_DIR})

link_directories(${CMAKE_SOURCE_DIR}/external/bin)


#add_library(${PROJECT_NAME}_shared SHARED ${SOURCES})
add_library(${PROJECT_NAME}_static STATIC ${SOURCES})
add_library(${PROJECT_NAME}_object OBJECT ${SOURCES})

add_subdirectory(unit_tests)

