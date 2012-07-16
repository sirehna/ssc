cmake_minimum_required (VERSION 2.6)
project (decode_unit)
#FILE(GLOB SRC source/*.c*) <- don't use this: specifying the files manually in the CMakeLists.txt file means that
# the generated Makefile will automatically re-run cmake when adding or removing a file in the CMakeLists.txt file
# whereas otherwise, cmake must be re-run manually when adding or removing a file
include_directories (include)
FILE(GLOB SRC source/DecodeUnit.cpp)
SET (LIB_TYPE SHARED)

add_definitions(-DNDEBUG)

add_library (${PROJECT_NAME}_static OBJECT ${SRC})
add_library (${PROJECT_NAME} SHARED ${SRC})

set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/include                                                                               CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")
set(${PROJECT_NAME}_LIBRARIES        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}         CACHE FILEPATH "${PROJECT_NAME}'s shared library")
set(${PROJECT_NAME}_STATIC_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}_static${CMAKE_STATIC_LIBRARY_SUFFIX}  CACHE FILEPATH "${PROJECT_NAME}'s static library")
set(${PROJECT_NAME}_FOUND            TRUE                                                                                                            CACHE BOOL     "Is ${PROJECT_NAME} available to other modules?")
