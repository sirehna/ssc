cmake_minimum_required (VERSION 2.6)
project (geometry)
set(SOURCES src/PointInPolygon.cpp
            src/PointInCartesianPolygon.cpp
            src/PointInSphericalPolygon.cpp
            src/PointInGeographicalPolygon.cpp
            src/LatitudeLongitude.cpp
            src/Angle.cpp
            src/Track.cpp
            src/Leg.cpp
            src/GreatCircle.cpp
            src/Vector3D.cpp
            src/Geometry.cpp
            src/Angle.cxx)

include_directories(inc)
include_directories(${exception_handling_INCLUDE_DIRS})
include_directories(${test_macros_SOURCE_DIR})
include_directories(SYSTEM ${boost_INCLUDE_DIRS})
include_directories(SYSTEM ${libgeographic_INCLUDE_DIRS})

add_library(${PROJECT_NAME}_object OBJECT ${SOURCES})

set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/inc                                                                               CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")
set(${PROJECT_NAME}_LIBRARIES        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}         CACHE FILEPATH "${PROJECT_NAME}'s shared library")
set(${PROJECT_NAME}_STATIC_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}_static${CMAKE_STATIC_LIBRARY_SUFFIX}  CACHE FILEPATH "${PROJECT_NAME}'s static library")
set(${PROJECT_NAME}_FOUND            TRUE                                                                                                            CACHE BOOL     "Is ${PROJECT_NAME} available to other modules?")

add_subdirectory(unit_tests)

