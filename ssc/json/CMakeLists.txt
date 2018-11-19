cmake_minimum_required (VERSION 2.6)
project (json)

set(SOURCES
    RapidJSON.hpp
    )

add_custom_target(json SOURCES ${SOURCES})

set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR} CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")
