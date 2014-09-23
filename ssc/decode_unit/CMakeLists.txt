cmake_minimum_required (VERSION 2.6)
project(decode_unit)
FILE(GLOB SRC DecodeUnit.cpp)

include_directories(${SSC_INCLUDE_DIRS})

add_definitions(-DNDEBUG)

add_library(${PROJECT_NAME}_object OBJECT ${SRC})
