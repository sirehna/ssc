cmake_minimum_required (VERSION 2.6)
project (geometry)

# Using C++ 2011
# The -std=c++0x option causes g++ to go into 'strict ANSI' mode so it doesn't declare non-standard functions
# (and _stricmp() is non-standard - it's just a version of strcmp() that's case-insensitive).
# Use -std=gnu++0x instead.
IF (NOT(MSVC))
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
ENDIF()

set(SRC src/PointInPolygon.cpp
        src/PointInCartesianPolygon.cpp
        src/PointInSphericalPolygon.cpp
        src/PointInGeographicalPolygon.cpp
        src/LatitudeLongitude.cpp
        src/Angle.cpp
        src/Track.cpp
        src/ShortestPathLeg.cpp
        src/GreatCircle.cpp
        src/Vector3D.cpp
        src/Geometry.cpp
        src/Angle.cxx
        src/Leg.cpp
        src/loxodrome_on_ellipsoid.cpp
        src/ConstantAzimuthLeg.cpp
        src/epsilon_algorithm.cpp
        src/LegChain.cpp
        src/ShortestPathLegChain.cpp
        src/ConstantAzimuthLegChain.cpp
            )

include_directories(inc)
include_directories(${SSC_INCLUDE_DIRS})
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
include_directories(SYSTEM ${geographiclib_INCLUDE_DIRS})

ADD_LIBRARY(${PROJECT_NAME}_object OBJECT ${SRC})

add_subdirectory(unit_tests)

