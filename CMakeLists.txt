cmake_minimum_required (VERSION 2.8.8)
project (matrix_and_vector_classes)

SET (${PROJECT_NAME}_build_shared OFF CACHE BOOL "Build shared library (i.e. DLL under Windows)")
SET (${PROJECT_NAME}_build_static ON CACHE BOOL "Build static library")

FILE(GLOB SRC src/SparseMatrix.cpp
              src/SparseVector.cpp)
set(ALL_SRC ${ALL_SRC} ${SRC} PARENT_SCOPE)
function(check_module_available module_name)
	if (NOT ${module_name}_FOUND)
		message(FATAL_ERROR "Error: cannot find ${module_name}")
	else()
		include_directories(${${module_name}_INCLUDE_DIRS})
		if (${${PROJECT_NAME}_build_shared})
			target_link_libraries(${PROJECT_NAME} ${${module_name}_LIBRARIES})
		endif()
	endif()
endfunction(check_module_available)

if (NOT test_macros_FOUND)
	find_path(test_macros_SOURCE_DIR "test_macros.hpp"
	          HINTS ${CMAKE_CURRENT_SOURCE_DIR}/../../Tools/macros REQUIRED)
endif()
include_directories(${test_macros_SOURCE_DIR})

if (${${PROJECT_NAME}_build_shared})
	add_library(${PROJECT_NAME} SHARED ${SRC})
endif()
if (${${PROJECT_NAME}_build_static})
	add_library(${PROJECT_NAME}_static OBJECT ${SRC})
endif()

check_module_available(exception_handling)

include_directories (${${PROJECT_NAME}_SOURCE_DIR}/inc)
  
set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/inc                                                                               CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")
set(${PROJECT_NAME}_LIBRARIES        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}         CACHE FILEPATH "${PROJECT_NAME}'s shared library")
set(${PROJECT_NAME}_STATIC_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}_static${CMAKE_STATIC_LIBRARY_SUFFIX}  CACHE FILEPATH "${PROJECT_NAME}'s static library")
set(${PROJECT_NAME}_FOUND            TRUE                                                                                                            CACHE BOOL     "Is ${PROJECT_NAME} available to other modules?")

add_subdirectory(unit_tests)
