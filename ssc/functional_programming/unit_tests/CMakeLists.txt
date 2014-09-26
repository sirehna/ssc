# ------8<---[LINES TO MODIFY WHEN CHANGING MODULE]----->8-----
set(MODULE_UNDER_TEST functional_programming)
project (${MODULE_UNDER_TEST}_tests)
FILE(GLOB SRC src/for_allTest.cpp)
              
# ------8<---------------------------------------------->8-----


# Include directories
include_directories(inc)

add_library (${PROJECT_NAME} OBJECT ${SRC})

include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
include_directories(${random_data_generator_INCLUDE_DIRS})
include_directories(${exception_handling_INCLUDE_DIRS})
