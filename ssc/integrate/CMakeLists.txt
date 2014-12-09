# CMake project file for QUADPACK

cmake_minimum_required (VERSION 2.6)
project (integrate)

# Using C++ 2011
# The -std=c++0x option causes g++ to go into 'strict ANSI' mode so it doesn't declare non-standard functions
# (and _stricmp() is non-standard - it's just a version of strcmp() that's case-insensitive).
# Use -std=gnu++0x instead.
IF(NOT(MSVC))
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
ENDIF()

SET(CMAKE_C_FLAGS "")

INCLUDE_DIRECTORIES(inc)
INCLUDE_DIRECTORIES(${SSC_INCLUDE_DIRS})

IF(CMAKE_SIZEOF_VOID_P EQUAL 8) # If on a 64 bit machine
    IF(UNIX AND NOT WIN32) # If on Linux
        SET(CMAKE_C_FLAGS "-fPIC")
    ENDIF()
ENDIF()

ADD_LIBRARY(${PROJECT_NAME}_object OBJECT TrapezoidalIntegration.cpp
                                          Simpson.cpp
                                          Integrator.cpp
                                          QuadPack.cpp
                                          GaussKronrod.cpp
                                          Rectangle.cpp
                                          Cumulate.cpp
                                          d1mach.c
                                          dqags.c
                                          dqagse.c
                                          dqelg.c
                                          dqk21.c
                                          dqpsrt.c
                                          qawoe.c
                                          qc25f.c
                                          qcheb.c
                                          qelg.c
                                          qk15w.c
                                          qpsrt.c
                                          qwgtf.c
                                          sgtsl.c
                                          r1mach.c
                                          )

add_subdirectory(unit_tests)
