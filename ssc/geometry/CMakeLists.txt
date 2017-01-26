CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(geometry)

# Using C++ 2011
# The -std=c++0x option causes g++ to go into 'strict ANSI' mode so it doesn't declare non-standard functions
# (and _stricmp() is non-standard - it's just a version of strcmp() that's case-insensitive).
# Use -std=gnu++0x instead.
IF (NOT(MSVC))
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
ENDIF()

SET(SRC PointInPolygon.cpp
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

INCLUDE_DIRECTORIES(inc)
INCLUDE_DIRECTORIES(${SSC_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(SYSTEM ${geographiclib_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(SYSTEM ${Boost_INCLUDE_DIRS})

ADD_LIBRARY(${PROJECT_NAME}_object OBJECT ${SRC})

ADD_SUBDIRECTORY(unit_tests)

