cmake_minimum_required (VERSION 2.6)
project (lpsolve_interface)
set(SOURCES src/LPSolver.cpp
            )

include_directories(inc)
include_directories(${test_macros_SOURCE_DIR})
include_directories(${${MODULE_UNDER_TEST}_INCLUDE_DIRS})
include_directories(${exception_handling_INCLUDE_DIRS})
include_directories(${functors_for_optimizer_INCLUDE_DIRS})
include_directories(${optimizer_INCLUDE_DIRS})
include_directories(${lp_solve_INCLUDE_DIRS})
include_directories(${matrix_and_vector_classes_INCLUDE_DIRS})

add_library(${PROJECT_NAME}_object OBJECT ${SOURCES})

set(${PROJECT_NAME}_INCLUDE_DIRS ${${PROJECT_NAME}_SOURCE_DIR}/inc CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")

add_subdirectory(unit_tests)

