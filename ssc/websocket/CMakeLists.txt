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

SET(USE_BOOST_FOR_WEBSOCKETPP 0)
IF(WIN32)
    IF(CMAKE_COMPILER_IS_GNUCC)
        MESSAGE(STATUS "WEBSOCKET -- Checking GCC version for WebsocketPP")
        IF(GCC_VERSION VERSION_LESS 4.6)
            MESSAGE(STATUS "WEBSOCKET -- Use Boost for WebsocketPP instead of STL")
            SET(USE_BOOST_FOR_WEBSOCKETPP 1)
        ELSE()
            MESSAGE(STATUS "WEBSOCKET -- Use STL for WebsocketPP instead of Boost")
        ENDIF()
    ENDIF()
ENDIF()

IF(USE_BOOST_FOR_WEBSOCKETPP)
    IF(WIN32)
        # http://msdn.microsoft.com/en-us/library/windows/desktop/aa383745%28v=vs.85%29.aspx
        # http://boost.2283326.n4.nabble.com/boost-asio-UnregisterWaitEx-RegisterWaitForSingleObject-has-not-been-declared-td4633963.html
        ADD_DEFINITIONS(-D_WIN32_WINNT=0x0501)
        ADD_DEFINITIONS(-DWINVER=0x0501)
    ENDIF()
ELSE()
    ADD_DEFINITIONS(-D_WEBSOCKETPP_CPP11_STL_)
    ADD_DEFINITIONS(-D_WEBSOCKETPP_CPP11_THREAD_)
    ADD_DEFINITIONS(-D_WEBSOCKETPP_CPP11_SYSTEM_ERROR_)
ENDIF()

IF(WIN32)
    # By default WebSocket++ performs block masking/unmasking in a manner that
    # makes assumptions about the nature of the machine and STL library used.
    # In particular the assumption is either a 32 or 64 bit word size and an
    # STL with std::string::data returning a contiguous char array.
    #
    # This method improves masking performance by 3-8x depending on the ratio
    # of small to large messages and the availability of a 64 bit processor.
    #
    # To disable this optimization (for use with alternative STL
    # implementations or processors) define WEBSOCKETPP_STRICT_MASKING when
    # compiling the library. This will force the library to perform masking in
    # single byte chunks.
    #
    # https://github.com/zaphoyd/websocketpp/blob/master/websocketpp/processors/hybi13.hpp
    # https://github.com/zaphoyd/websocketpp/issues/423
    #
    # This option is at least required for MinGW 64 bits
    # It may be uncessary for MSVC.
    ADD_DEFINITIONS(-DWEBSOCKETPP_STRICT_MASKING)
ENDIF()
INCLUDE_DIRECTORIES(inc)
INCLUDE_DIRECTORIES(${SSC_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(SYSTEM ${websocketpp_INCLUDE_DIR})
INCLUDE_DIRECTORIES(SYSTEM ${Boost_INCLUDE_DIRS})

ADD_LIBRARY(${PROJECT_NAME}_object OBJECT ${SRC})

SET(${PROJECT_NAME}_INCLUDE_DIRS ${${PROJECT_NAME}_SOURCE_DIR}/inc CACHE PATH "Path to ${PROJECT_NAME}'s include directory")

ADD_SUBDIRECTORY(unit_tests)
