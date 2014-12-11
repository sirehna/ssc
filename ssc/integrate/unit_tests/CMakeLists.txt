# ------8<---[LINES TO MODIFY WHEN CHANGING MODULE]----->8-----
set(MODULE_UNDER_TEST integrate)
project (${MODULE_UNDER_TEST}_tests)

FILE(GLOB SRC src/TrapezoidalIntegrationTest.cpp
              src/SimpsonTest.cpp
              src/GaussKronrodTest.cpp
              src/CumulateTest.cpp
              src/RectangleTest.cpp
              src/ClenshawCurtisTest.cpp
              src/FilonTest.cpp
              src/dci.c
              src/dsi.c
              src/dcsevl.c
              src/initds.c
              src/d9sifg.c    
              )

SET(CMAKE_C_FLAGS "")
IF(CMAKE_SIZEOF_VOID_P EQUAL 8) # If on a 64 bit machine
    IF(UNIX AND NOT WIN32) # If on Linux
        SET(CMAKE_C_FLAGS "-fPIC")
    ENDIF()
ENDIF()

# ------8<---------------------------------------------->8-----

# Include directories
include_directories(inc)
include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
include_directories(${SSC_INCLUDE_DIRS})

add_library (${PROJECT_NAME} OBJECT ${SRC})


