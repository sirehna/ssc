# ------8<---[LINES TO MODIFY WHEN CHANGING MODULE]----->8-----
set(MODULE_UNDER_TEST data_retrievers)
project (${MODULE_UNDER_TEST}_tests)
FILE(GLOB SRC src/DataSourceTest.cpp)
# ------8<---------------------------------------------->8-----

set(exception_handling_dir "${CMAKE_CURRENT_BINARY_DIR}/../../exception_handling")
set(random_data_generator_dir "${CMAKE_CURRENT_BINARY_DIR}/../../random_data_generator")

find_library(exception_handling_LIBRARIES NAME ${CMAKE_STATIC_LIBRARY_PREFIX}exception_handling_static${CMAKE_STATIC_LIBRARY_SUFFIX}
             HINTS ${exception_handling_dir})
find_library(random_data_generator_LIBRARIES NAME ${CMAKE_STATIC_LIBRARY_PREFIX}random_data_generator_static${CMAKE_STATIC_LIBRARY_SUFFIX}
             HINTS ${random_data_generator_dir})
enable_testing()

# Include directories
include_directories(inc)
include_directories(${${MODULE_UNDER_TEST}_INCLUDE_DIRS})
include_directories(${random_data_generator_INCLUDE_DIRS})
include_directories(${yaml_parser_INCLUDE_DIRS})
include_directories(SYSTEM ${YAMLCPP_INCLUDE_DIR})

add_library (${PROJECT_NAME} OBJECT ${SRC})


ADD_DEPENDENCIES(${PROJECT_NAME} googlemock test_macros)
ADD_DEPENDENCIES(${PROJECT_NAME} random_data_generator)


include_directories(SYSTEM ${GTEST_INCLUDE_DIR})
include_directories(${random_data_generator_INCLUDE_DIR})