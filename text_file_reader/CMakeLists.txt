cmake_minimum_required (VERSION 2.8.8)
project (text_file_reader)


FILE(GLOB SRC src/TextFileReader.cpp)
set(ALL_SRC ${ALL_SRC} ${SRC} PARENT_SCOPE)
if (NOT test_macros_FOUND)
	find_path(test_macros_SOURCE_DIR "test_macros.hpp"
	          HINTS ${CMAKE_CURRENT_SOURCE_DIR}/../../Tools/macros REQUIRED)
endif()

include_directories(${test_macros_SOURCE_DIR})

SET (${PROJECT_NAME}_build_shared OFF CACHE BOOL "Build shared library (i.e. DLL under Windows)")
SET (${PROJECT_NAME}_build_static ON CACHE BOOL "Build static library")


if (${${PROJECT_NAME}_build_shared})
	add_library(${PROJECT_NAME} SHARED ${SRC})
endif()
if (${${PROJECT_NAME}_build_static})
	add_library(${PROJECT_NAME}_static OBJECT ${SRC})
endif()

include_directories (${${PROJECT_NAME}_SOURCE_DIR}/inc)
include_directories(${exception_handling_INCLUDE_DIRS})

# Using C++ 2011
# The -std=c++0x option causes g++ to go into 'strict ANSI' mode so it doesn't declare non-standard functions
# (and _stricmp() is non-standard - it's just a version of strcmp() that's case-insensitive).
# Use -std=gnu++0x instead.
ADD_DEFINITIONS("-std=gnu++0x")

set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/inc                                                                               CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")
set(${PROJECT_NAME}_LIBRARIES        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}         CACHE FILEPATH "${PROJECT_NAME}'s shared library")
set(${PROJECT_NAME}_STATIC_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}_static${CMAKE_STATIC_LIBRARY_SUFFIX}  CACHE FILEPATH "${PROJECT_NAME}'s static library")
set(${PROJECT_NAME}_FOUND            TRUE                                                                                                            CACHE BOOL     "Is ${PROJECT_NAME} available to other modules?")

add_subdirectory(unit_tests)