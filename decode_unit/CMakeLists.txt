cmake_minimum_required (VERSION 2.6)
project(decode_unit)
FILE(GLOB SRC source/DecodeUnit.cpp)

include_directories(include)
add_definitions(-DNDEBUG)

add_library(${PROJECT_NAME}_object OBJECT ${SRC})
set(${PROJECT_NAME}_INCLUDE_DIRS ${${PROJECT_NAME}_SOURCE_DIR}/include CACHE PATH "Path to ${PROJECT_NAME}'s include directory")
