cmake_minimum_required (VERSION 2.6)
project (ipopt_interface)
set(SOURCES InternalIpopt.cpp
            IpoptParameters.cpp
            IpoptSolver.cpp)

include_directories(private_includes)
include_directories(${test_macros_SOURCE_DIR})
include_directories(${${MODULE_UNDER_TEST}_INCLUDE_DIRS})
include_directories(${random_data_generator_INCLUDE_DIRS})
include_directories(${exception_handling_INCLUDE_DIRS})
include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
include_directories(${SSC_INCLUDE_DIRS})
include_directories(SYSTEM ${IPOPT_INCLUDE_DIRS})

# Using C++ 2011
# The -std=c++0x option causes g++ to go into 'strict ANSI' mode so it doesn't declare non-standard functions
# (and _stricmp() is non-standard - it's just a version of strcmp() that's case-insensitive).
# Use -std=gnu++0x instead.
IF (NOT(MSVC))
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
ENDIF()

add_definitions(-DHAVE_CONFIG_H)

add_library(${PROJECT_NAME}_object OBJECT ${SOURCES})

set(${PROJECT_NAME}_INCLUDE_DIRS ${${PROJECT_NAME}_SOURCE_DIR}/inc CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")

add_subdirectory(unit_tests)

