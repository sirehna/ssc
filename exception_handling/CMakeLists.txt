cmake_minimum_required (VERSION 2.6)
project (exception_handling)
FILE(GLOB SRC src/Exception.cpp)

include_directories(inc)

add_library (${PROJECT_NAME}_static OBJECT ${SRC})

set(${PROJECT_NAME}_INCLUDE_DIRS ${${PROJECT_NAME}_SOURCE_DIR}/inc CACHE PATH "Path to ${PROJECT_NAME}'s include directory")
