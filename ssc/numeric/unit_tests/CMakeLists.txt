# ------8<---[LINES TO MODIFY WHEN CHANGING MODULE]----->8-----
set(MODULE_UNDER_TEST numeric)
project(${MODULE_UNDER_TEST}_tests)
FILE(GLOB SRC src/kahan_sumTest.cpp
              src/pairwise_sumTest.cpp
              src/almost_equalTest.cpp
              )
# ------8<---------------------------------------------->8-----

# Use C++11 to simplify tests
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")

# Include directories
include_directories(inc)
include_directories(${SSC_INCLUDE_DIRS})
include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(SYSTEM ${Boost_INCLUDE_DIRS})

add_library(${PROJECT_NAME} OBJECT ${SRC})
