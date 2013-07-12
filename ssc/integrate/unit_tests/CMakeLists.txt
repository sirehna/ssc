# ------8<---[LINES TO MODIFY WHEN CHANGING MODULE]----->8-----
set(MODULE_UNDER_TEST integrate)
project (${MODULE_UNDER_TEST}_tests)

FILE(GLOB SRC src/TrapezoidalIntegrationTest.cpp
              src/SimpsonTest.cpp
              src/QuadPackTest.cpp)


# ------8<---------------------------------------------->8-----

SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Woverloaded-virtual -Wwrite-strings -DGTEST_HAS_PTHREAD=0")


# Include directories
include_directories(inc)
include_directories(${test_macros_SOURCE_DIR})
include_directories(${${MODULE_UNDER_TEST}_INCLUDE_DIRS})
include_directories(${random_data_generator_INCLUDE_DIRS})
include_directories(SYSTEM ${GTEST_INCLUDE_DIR})

add_library (${PROJECT_NAME} OBJECT ${SRC})


