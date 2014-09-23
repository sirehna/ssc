# ------8<---[LINES TO MODIFY WHEN CHANGING MODULE]----->8-----
set(MODULE_UNDER_TEST data_source)
project (${MODULE_UNDER_TEST}_tests)
FILE(GLOB SRC src/DataSourceTest.cpp
              src/SignalContainerTest.cpp
              src/TypeCoercionTest.cpp)
# ------8<---------------------------------------------->8-----

# Include directories
include_directories(SYSTEM inc)
include_directories(${SSC_INCLUDE_DIRS})
include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
include_directories(SYSTEM ${GMOCK_INCLUDE_DIRS})

add_library (${PROJECT_NAME} OBJECT ${SRC})
