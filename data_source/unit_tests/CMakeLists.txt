# ------8<---[LINES TO MODIFY WHEN CHANGING MODULE]----->8-----
set(MODULE_UNDER_TEST data_source)
project (${MODULE_UNDER_TEST}_tests)
FILE(GLOB SRC src/DataSourceTest.cpp)
              
# ------8<---------------------------------------------->8-----

# Include directories
include_directories(inc)
include_directories(${${MODULE_UNDER_TEST}_INCLUDE_DIRS})
include_directories(${random_data_generator_INCLUDE_DIRS})
include_directories(${test_macros_SOURCE_DIR})

add_library (${PROJECT_NAME} OBJECT ${SRC})


link_directories(${CMAKE_CURRENT_BINARY_DIR}/random_data_generator)
ADD_DEPENDENCIES(${PROJECT_NAME} random_data_generator)


include_directories(SYSTEM ${GTEST_INCLUDE_DIR})
include_directories(${random_data_generator_INCLUDE_DIR})