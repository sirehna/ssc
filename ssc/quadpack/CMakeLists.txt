# CMake project file for QUADPACK

cmake_minimum_required (VERSION 2.6)
project (quadpack)
#enable_language (Fortran)
#    set (CMAKE_Fortran_FLAGS_RELEASE "-funroll-all-loops -fno-f2c -O3 -m32 -g3 -pedantic -pedantic-errors -fpedantic -w -Wno-globals -Wunused -Wuninitialized -Wall -Wsurprising -Werror -W")
#    set (CMAKE_Fortran_FLAGS_DEBUG   "-fno-f2c -O0 -g3 -m32 -pedantic -pedantic-errors -pedantic -w -Wno-globals -Wunused -Wuninitialized -Wall -Wsurprising -Werror -W")
     
#add_library(${PROJECT_NAME}_object OBJECT d1mach.f
#                                   dqags.f
#                                   dqagse.f
#                                   dqelg.f
#                                   dqk21.f
#                                   dqpsrt.f)

include_directories(inc)
include_directories(${test_macros_SOURCE_DIR})
add_library(${PROJECT_NAME}_object OBJECT src/TrapezoidalIntegration.cpp
                                          src/Simpson.cpp)


add_subdirectory(unit_tests)
