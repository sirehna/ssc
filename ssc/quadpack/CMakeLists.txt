# CMake project file for QUADPACK

cmake_minimum_required (VERSION 2.6)
project (quadpack)

enable_language (Fortran)
    set (CMAKE_Fortran_FLAGS_RELEASE "-funroll-all-loops -fno-f2c -O3 -m32 -g3 -pedantic -pedantic-errors -fpedantic -w -Wno-globals -Wunused -Wuninitialized -Wall -Wsurprising -Werror -W")
    set (CMAKE_Fortran_FLAGS_DEBUG   "-fno-f2c -O0 -g3 -m32 -pedantic -pedantic-errors -pedantic -w -Wno-globals -Wunused -Wuninitialized -Wall -Wsurprising -Werror -W")

include_directories(inc)
     
add_library(${PROJECT_NAME}_object OBJECT d1mach.f
                                   dqags.f
                                   dqagse.f
                                   dqelg.f
                                   dqk21.f
                                   dqpsrt.f)



set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/inc                                                                               CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")
set(${PROJECT_NAME}_LIBRARIES        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}         CACHE FILEPATH "${PROJECT_NAME}'s shared library")
set(${PROJECT_NAME}_STATIC_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}_static${CMAKE_STATIC_LIBRARY_SUFFIX}  CACHE FILEPATH "${PROJECT_NAME}'s static library")
set(${PROJECT_NAME}_FOUND            TRUE                                                                                                            CACHE BOOL     "Is ${PROJECT_NAME} available to other modules?")



#add_subdirectory(unit_tests)

#enable_language (Fortran)
#    set (CMAKE_Fortran_FLAGS_RELEASE "-funroll-all-loops -fno-f2c -O3 -m32 -g3 -pedantic -pedantic-errors -fpedantic -w -Wno-globals -Wunused -Wuninitialized -Wall -Wsurprising -Werror -W")
#    set (CMAKE_Fortran_FLAGS_DEBUG   "-fno-f2c -O0 -g3 -m32 -pedantic -pedantic-errors -pedantic -w -Wno-globals -Wunused -Wuninitialized -Wall -Wsurprising -Werror -W")
     
#add_library(${PROJECT_NAME}_object OBJECT d1mach.f
#                                   dqags.f
#                                   dqagse.f
#                                   dqelg.f
#                                   dqk21.f
#                                   dqpsrt.f)

#include_directories(inc)

#add_library(${PROJECT_NAME}_object OBJECT src/Integrate.cpp)


#add_subdirectory(unit_tests)

