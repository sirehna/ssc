# ------8<---[LINES TO MODIFY WHEN CHANGING MODULE]----->8-----
set(MODULE_UNDER_TEST integrate)
project (${MODULE_UNDER_TEST}_tests)

FILE(GLOB SRC src/TrapezoidalIntegrationTest.cpp
              src/SimpsonTest.cpp
              src/QuadPackTest.cpp
              src/CumulateTest.cpp
              src/RectangleTest.cpp
              )


# ------8<---------------------------------------------->8-----

# Include directories
include_directories(inc)
include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
include_directories(${SSC_INCLUDE_DIRS})

add_library (${PROJECT_NAME} OBJECT ${SRC})


