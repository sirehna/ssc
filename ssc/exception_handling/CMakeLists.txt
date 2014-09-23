CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(exception_handling)
set(SRC Exception.cpp)

include_directories(${SSC_INCLUDE_DIRS})
ADD_LIBRARY(${PROJECT_NAME}_object OBJECT ${SRC})
