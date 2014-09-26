cmake_minimum_required (VERSION 2.6)
project (geometry)

# Using C++ 2011
# The -std=c++0x option causes g++ to go into 'strict ANSI' mode so it doesn't declare non-standard functions
# (and _stricmp() is non-standard - it's just a version of strcmp() that's case-insensitive).
# Use -std=gnu++0x instead.
IF (NOT(MSVC))
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
ENDIF()

set(SRC PointInPolygon.cpp
        PointInCartesianPolygon.cpp
        PointInSphericalPolygon.cpp
        PointInGeographicalPolygon.cpp
        LatitudeLongitude.cpp
        Angle.cpp
        Track.cpp
        ShortestPathLeg.cpp
        GreatCircle.cpp
        Vector3D.cpp
        Geometry.cpp
        Angle.cxx
        Leg.cpp
        loxodrome_on_ellipsoid.cpp
        ConstantAzimuthLeg.cpp
        epsilon_algorithm.cpp
        LegChain.cpp
        ShortestPathLegChain.cpp
        ConstantAzimuthLegChain.cpp
            )

include_directories(inc)
include_directories(${SSC_INCLUDE_DIRS})
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
include_directories(SYSTEM ${geographiclib_INCLUDE_DIRS})

ADD_LIBRARY(${PROJECT_NAME}_object OBJECT ${SRC})

add_subdirectory(unit_tests)

