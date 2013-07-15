cmake_minimum_required (VERSION 2.8.8)
project (yaml_parser)

FILE(GLOB SRC src/YamlParser.cpp)

include_directories(${test_macros_INCLUDE_DIRS})
include_directories(inc)
include_directories(SYSTEM ${YAML_CPP_INCLUDE_DIRS})

# Using C++ 2011
# The -std=c++0x option causes g++ to go into 'strict ANSI' mode so it doesn't declare non-standard functions
# (and _stricmp() is non-standard - it's just a version of strcmp() that's case-insensitive).
# Use -std=gnu++0x instead.
ADD_DEFINITIONS("-std=gnu++0x")
  
set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/inc                                                                               CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")
add_library (${PROJECT_NAME}_static STATIC ${SRC})
