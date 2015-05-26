CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)
PROJECT(websocket)

SET(SRC src/ConnectionMetadata.cpp
        src/WebSocketClient.cpp
        src/WebSocketMessage.cpp
        src/WebSocketMessageImpl.cpp
        src/WebSocketServer.cpp
        )

# Using C++ 2011
# The -std=c++0x option causes g++ to go into 'strict ANSI' mode so it doesn't declare non-standard functions
# (and _stricmp() is non-standard - it's just a version of strcmp() that's case-insensitive).
# Use -std=gnu++0x instead.
IF(NOT(MSVC))
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
ENDIF()

ADD_DEFINITIONS(-D_WEBSOCKETPP_CPP11_STL_)
ADD_DEFINITIONS(-D_WEBSOCKETPP_CPP11_THREAD_)
ADD_DEFINITIONS(-D_WEBSOCKETPP_CPP11_SYSTEM_ERROR_)
INCLUDE_DIRECTORIES(inc)
INCLUDE_DIRECTORIES(${SSC_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(SYSTEM ${websocketpp_INCLUDE_DIR})
INCLUDE_DIRECTORIES(SYSTEM ${Boost_INCLUDE_DIRS})

ADD_LIBRARY(${PROJECT_NAME}_object OBJECT ${SRC})

SET(${PROJECT_NAME}_INCLUDE_DIRS ${${PROJECT_NAME}_SOURCE_DIR}/inc CACHE PATH "Path to ${PROJECT_NAME}'s include directory")

ADD_SUBDIRECTORY(unit_tests)
