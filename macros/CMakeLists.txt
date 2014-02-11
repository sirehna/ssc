cmake_minimum_required (VERSION 2.6)
project (test_macros)

set(SOURCES
    test_macros.hpp
    extra_test_assertions.hpp)

add_custom_target(test_macros SOURCES ${SOURCES})

set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR} CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")
