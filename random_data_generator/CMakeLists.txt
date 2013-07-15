cmake_minimum_required (VERSION 2.6)
project (random_data_generator)

FILE(GLOB SRC src/DataGenerator.cpp
              src/sir_rand.c)
SET_SOURCE_FILES_PROPERTIES(src/sir_rand.c PROPERTIES LANGUAGE CXX ) # Force the use of a C++ compiler on sir_rand.c (doesn't link otherwise)

include_directories(inc)

#add_library(${PROJECT_NAME} SHARED ${SRC})
add_library (${PROJECT_NAME}_static STATIC ${SRC})

set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/inc                                                                               CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")
#set(${PROJECT_NAME}_LIBRARIES        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}         CACHE FILEPATH "${PROJECT_NAME}'s shared library")
#set(${PROJECT_NAME}_STATIC_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}_static${CMAKE_STATIC_LIBRARY_SUFFIX}  CACHE FILEPATH "${PROJECT_NAME}'s static library")

add_subdirectory(unit_tests)

