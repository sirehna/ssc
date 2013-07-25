#cmake_minimum_required (VERSION 2.8.8)
#project (functional_programming)

set(SOURCES src/for_all.cpp)

            
#add_custom_target(${PROJECT_NAME} SOURCES ${SOURCES})
#set(${PROJECT_NAME}_FOUND TRUE CACHE BOOL "Is ${PROJECT_NAME} available to other modules?")

include_directories(inc)

# Using C++ 2011
# The -std=c++0x option causes g++ to go into 'strict ANSI' mode so it doesn't declare non-standard functions
# (and _stricmp() is non-standard - it's just a version of strcmp() that's case-insensitive).
# Use -std=gnu++0x instead.
ADD_DEFINITIONS("-std=gnu++0x")

#add_library(${PROJECT_NAME}_static OBJECT ${SOURCES})

set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/inc                                                                               CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")

add_subdirectory(unit_tests)
