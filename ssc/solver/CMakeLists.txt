cmake_minimum_required (VERSION 2.8.8)
project (solver)

include_directories(${SSC_INCLUDE_DIRS})
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

add_subdirectory(unit_tests)
