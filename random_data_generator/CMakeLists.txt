cmake_minimum_required (VERSION 2.6)
project (random_data_generator)

FILE(GLOB SRC src/DataGenerator.cpp
              src/sir_rand.c)
SET_SOURCE_FILES_PROPERTIES(src/sir_rand.c PROPERTIES LANGUAGE CXX ) # Force the use of a C++ compiler on sir_rand.c (doesn't link otherwise)

if (NOT test_macros_FOUND)
	find_path(test_macros_SOURCE_DIR "test_macros.hpp"
	          HINTS ${CMAKE_CURRENT_SOURCE_DIR}/../macros REQUIRED)
endif()

include_directories(${test_macros_SOURCE_DIR})

  
SET (${PROJECT_NAME}_build_shared 0 CACHE BOOL "Build shared library (i.e. DLL under Windows)")
SET (${PROJECT_NAME}_build_static 1 CACHE BOOL "Build static library")

include_directories (${${PROJECT_NAME}_SOURCE_DIR}/inc)
if (${${PROJECT_NAME}_build_shared})
	add_library(${PROJECT_NAME} SHARED ${SRC})
endif()
if (${${PROJECT_NAME}_build_static})
	add_library (${PROJECT_NAME}_static OBJECT ${SRC})
endif()

set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/inc                                                                               CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")
set(${PROJECT_NAME}_LIBRARIES        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}         CACHE FILEPATH "${PROJECT_NAME}'s shared library")
set(${PROJECT_NAME}_STATIC_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}_static${CMAKE_STATIC_LIBRARY_SUFFIX}  CACHE FILEPATH "${PROJECT_NAME}'s static library")
set(${PROJECT_NAME}_FOUND            TRUE                                                                                                            CACHE BOOL     "Is ${PROJECT_NAME} available to other modules?")

add_subdirectory(unit_tests)
