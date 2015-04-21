cmake_minimum_required (VERSION 2.6)
project (optimizer)
set(SOURCES OptimizationProblem.cpp
            OptimizationResult.cpp)

include_directories(inc)
INCLUDE_DIRECTORIES(${SSC_INCLUDE_DIRS})

# Using C++ 2011
# The -std=c++0x option causes g++ to go into 'strict ANSI' mode so it doesn't declare non-standard functions
# (and _stricmp() is non-standard - it's just a version of strcmp() that's case-insensitive).
# Use -std=gnu++0x instead.
IF (NOT(MSVC))
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
ENDIF()

add_library(${PROJECT_NAME}_object OBJECT ${SOURCES})

add_subdirectory(unit_tests)

