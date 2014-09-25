CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)
PROJECT(kinematics)

# Using C++ 2011
# The -std=c++0x option causes g++ to go into 'strict ANSI' mode so it doesn't declare non-standard functions
# (and _stricmp() is non-standard - it's just a version of strcmp() that's case-insensitive).
# Use -std=gnu++0x instead.
IF (NOT(MSVC))
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
ENDIF()

SET(SRC Velocity.cpp
        rotation_matrix_builders.cpp
        EulerAngles.cpp
        Kinematics.cpp
        Point.cpp
        PointMatrix.cpp
        Transform.cpp
        KinematicTree.cpp
        Wrench.cpp
        UnsafeWrench.cpp
        coriolis_and_centripetal.cpp
        )

include_directories(${SSC_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(SYSTEM ${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(SYSTEM ${eigen_INCLUDE_DIRS})

ADD_LIBRARY(${PROJECT_NAME}_object OBJECT ${SRC})

ADD_SUBDIRECTORY(unit_tests)
