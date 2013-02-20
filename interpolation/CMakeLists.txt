cmake_minimum_required (VERSION 2.8.8)
project (interpolation)

FILE(GLOB SRC src/Splines.cpp
              src/NaturalSplines.cpp
              src/ParabolicRunoutSplines.cpp
              src/CubicRunoutSplines.cpp
              src/VectorOfEquallySpacedNumbers.cpp
              src/LinearInterpolation.cpp
              src/RAO.cpp
              src/PiecewiseConstant.cpp)

# Find exception_handling
set(exception_handling_dir "${CMAKE_CURRENT_BINARY_DIR}/../exception_handling")# PATH "Installation path of the exception_handling module" )

include_directories(${exception_handling_SOURCE_DIR}/inc)
include_directories(${test_macros_SOURCE_DIR})

# Using C++ 2011
# The -std=c++0x option causes g++ to go into 'strict ANSI' mode so it doesn't declare non-standard functions
# (and _stricmp() is non-standard - it's just a version of strcmp() that's case-insensitive).
# Use -std=gnu++0x instead.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wfatal-errors -pedantic -pedantic-errors -Wextra -Wall -Wunused-function -Wunused-label -Wunused-parameter -Wunused-value -Wunused-variable -Wvariadic-macros -fno-common -Wformat=2 -Winit-self -Wpacked -Wp,-D_FORTIFY_SOURCE=2 -Wpointer-arith -Wlarger-than-65500 -Wmissing-declarations -Wmissing-format-attribute -Wno-deprecated -Wsign-compare -Wstrict-aliasing=2 -Wundef -ffast-math -fomit-frame-pointer")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} -Woverloaded-virtual -Weffc++ -Wwrite-strings")
set(C_FLAGS "${CMAKE_C_FLAGS}")
set(CXX_FLAGS "${CMAKE_CXX_FLAGS}")
ADD_DEFINITIONS("-std=gnu++0x")

  
SET (${PROJECT_NAME}_build_shared OFF CACHE BOOL "Build shared library (i.e. DLL under Windows)")
SET (${PROJECT_NAME}_build_static ON CACHE BOOL "Build static library")
include_directories (${${PROJECT_NAME}_SOURCE_DIR}/inc)
if (${${PROJECT_NAME}_build_shared})
	add_library(${PROJECT_NAME} SHARED ${SRC})
	target_link_libraries(${PROJECT_NAME} ${exception_handling_LIBRARIES})
	target_link_libraries(${PROJECT_NAME} ${LAPACK_LIBRARIES})
endif()
if (${${PROJECT_NAME}_build_static})
	add_library (${PROJECT_NAME}_static OBJECT ${SRC})
endif()



set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/inc                                                                               CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")
set(${PROJECT_NAME}_LIBRARIES        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}         CACHE FILEPATH "${PROJECT_NAME}'s shared library")
set(${PROJECT_NAME}_STATIC_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}_static${CMAKE_STATIC_LIBRARY_SUFFIX}  CACHE FILEPATH "${PROJECT_NAME}'s static library")
set(${PROJECT_NAME}_FOUND            TRUE                                                                                                            CACHE BOOL     "Is ${PROJECT_NAME} available to other modules?")

add_subdirectory(unit_tests)
