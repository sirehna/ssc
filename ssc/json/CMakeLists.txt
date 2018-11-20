cmake_minimum_required (VERSION 2.6)
project (json)

set(SRC RapidJSON.cpp)

include_directories(${SSC_INCLUDE_DIRS})
ADD_LIBRARY(${PROJECT_NAME}_object OBJECT ${SRC})
