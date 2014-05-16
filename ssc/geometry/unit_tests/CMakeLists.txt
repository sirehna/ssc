# ------8<---[LINES TO MODIFY WHEN CHANGING MODULE]----->8-----
set(MODULE_UNDER_TEST geometry)
project (${MODULE_UNDER_TEST}_tests)
FILE(GLOB SRC src/PointInCartesianPolygonTest.cpp
              src/PointInSphericalPolygonTest.cpp
              src/PointInGeographicalPolygonTest.cpp
              src/LatitudeLongitudeGenerators.cpp
              src/LatitudeOfPointOnBorder.cpp
              src/LatitudeLongitudeTest.cpp
              src/AngleTest.cpp
              src/TrackTest.cpp
              src/ShortestPathLegTest.cpp
              src/TrackGenerator.cpp
              src/loxodrome_on_ellipsoidTest.cpp
              src/ConstantAzimuthLegTest.cpp
              )
# ------8<---------------------------------------------->8-----


# Include directories
include_directories(inc)
include_directories(${test_macros_SOURCE_DIR})
include_directories(${${MODULE_UNDER_TEST}_INCLUDE_DIRS})
include_directories(${random_data_generator_INCLUDE_DIRS})

add_library (${PROJECT_NAME} OBJECT ${SRC})

include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
include_directories(${random_data_generator_INCLUDE_DIRS})

set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/inc  CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")
