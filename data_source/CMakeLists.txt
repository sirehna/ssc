cmake_minimum_required (VERSION 2.8.8)
project (data_source)

set(SOURCES src/DataSource.cpp
            src/DataSourceModule.cpp)
            
#add_custom_target(${PROJECT_NAME} SOURCES ${SOURCES})
#set(${PROJECT_NAME}_INCLUDE_DIRS ${${PROJECT_NAME}_SOURCE_DIR}/inc  CACHE PATH "Path to ${PROJECT_NAME}'s include directory")

include_directories(inc)

add_library(${PROJECT_NAME}_object OBJECT ${SOURCES})

set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/inc                                                                               CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")
set(${PROJECT_NAME}_LIBRARIES        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}         CACHE FILEPATH "${PROJECT_NAME}'s shared library")
set(${PROJECT_NAME}_STATIC_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}_static${CMAKE_STATIC_LIBRARY_SUFFIX}  CACHE FILEPATH "${PROJECT_NAME}'s static library")

add_subdirectory(unit_tests)
