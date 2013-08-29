cmake_minimum_required (VERSION 2.6)
project (csv_file_reader)

FILE(GLOB SRC src/CSVFileReader.cpp)

include_directories(${exception_handling_SOURCE_DIR}/inc)
include_directories(${test_macros_SOURCE_DIR})

  
SET (${PROJECT_NAME}_build_shared 0 CACHE BOOL "Build shared library (i.e. DLL under Windows)")
SET (${PROJECT_NAME}_build_static 1 CACHE BOOL "Build static library")
include_directories (${${PROJECT_NAME}_SOURCE_DIR}/inc)
if (${${PROJECT_NAME}_build_shared})
	add_library(${PROJECT_NAME} SHARED ${SRC})
	target_link_libraries(${PROJECT_NAME} ${exception_handling_LIBRARIES})
endif()
if (${${PROJECT_NAME}_build_static})
	add_library (${PROJECT_NAME}_static OBJECT ${SRC})
endif()



set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/inc                                                                               CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")
set(${PROJECT_NAME}_LIBRARIES        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}         CACHE FILEPATH "${PROJECT_NAME}'s shared library")
set(${PROJECT_NAME}_STATIC_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}_static${CMAKE_STATIC_LIBRARY_SUFFIX}  CACHE FILEPATH "${PROJECT_NAME}'s static library")
set(${PROJECT_NAME}_FOUND            TRUE                                                                                                            CACHE BOOL     "Is ${PROJECT_NAME} available to other modules?")

add_subdirectory(unit_tests)