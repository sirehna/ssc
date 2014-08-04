cmake_minimum_required (VERSION 2.6)
project (optimizer)
set(SOURCES src/OptimizationProblem.cpp
            src/OptimizationResult.cpp)

include_directories(inc)
include_directories(${test_macros_SOURCE_DIR})
include_directories(${functors_for_optimizer_INCLUDE_DIRS})
include_directories(${exception_handling_INCLUDE_DIRS})
include_directories(${matrix_and_vector_classes_INCLUDE_DIRS})

# Using C++ 2011
# The -std=c++0x option causes g++ to go into 'strict ANSI' mode so it doesn't declare non-standard functions
# (and _stricmp() is non-standard - it's just a version of strcmp() that's case-insensitive).
# Use -std=gnu++0x instead.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")

add_library(${PROJECT_NAME}_object OBJECT ${SOURCES})

set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/inc                                                                               CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")
set(${PROJECT_NAME}_LIBRARIES        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}         CACHE FILEPATH "${PROJECT_NAME}'s shared library")
set(${PROJECT_NAME}_STATIC_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}_static${CMAKE_STATIC_LIBRARY_SUFFIX}  CACHE FILEPATH "${PROJECT_NAME}'s static library")
set(${PROJECT_NAME}_FOUND            TRUE                                                                                                            CACHE BOOL     "Is ${PROJECT_NAME} available to other modules?")


add_subdirectory(unit_tests)

