CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)
PROJECT(ssc)

set(${PROJECT_NAME}_MAJOR_VERSION 1)
set(${PROJECT_NAME}_MINOR_VERSION 0)
set(${PROJECT_NAME}_PATCH_VERSION 0)
set(${PROJECT_NAME}_VERSION
  ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_VERSION})
set(${PROJECT_NAME}_VERSION_STR
  ${${PROJECT_NAME}_MAJOR_VERSION}-${${PROJECT_NAME}_MINOR_VERSION}-${${PROJECT_NAME}_PATCH_VERSION})

#############################################################################
# CMake utilities
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
#############################################################################

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CMakeMacros.cmake)

set(ssc_MAJOR_VERSION "${${PROJECT_NAME}_MAJOR_VERSION}")
set(ssc_MINOR_VERSION "${${PROJECT_NAME}_MINOR_VERSION}")
set(ssc_PATCH_VERSION "${${PROJECT_NAME}_PATCH_VERSION}")
configure_file(ssc-config-version.cmake.in
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake" @ONLY)

INCLUDE(CTest)

SET(CMAKE_VERBOSE_MAKEFILE OFF)
#############################################################################
# User configuration
IF(NOT DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug)
ENDIF()

IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
   SET(ARCH64_BITS TRUE)
ELSE()
   SET(ARCH64_BITS FALSE)
ENDIF()

IF(DEFINED INSTALL_PREFIX)
    SET(CMAKE_INSTALL_PREFIX ${INSTALL_PREFIX})
ELSE()
    SET(CMAKE_INSTALL_PREFIX ../install${CMAKE_BUILD_TYPE})
ENDIF()
MESSAGE(STATUS "CMAKE_INSTALL_PREFIX :${CMAKE_INSTALL_PREFIX}")

# GIT SHA
INCLUDE(GetGitRevisionDescription)
GET_GIT_HEAD_REVISION(GIT_REFSPEC GIT_SHA1)
MESSAGE(STATUS "GIT_SHA1 : ${GIT_SHA1}")
CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/Copyright.txt"
               "${CMAKE_CURRENT_BINARY_DIR}/Copyright.txt" @ONLY)
#############################################################################
INCLUDE(CMakeGMock)

INCLUDE(CMakeOutputDirectories)

#############################################################################
# Third party libraries
# Boost
# -> Require at least version 1.53 of boost to use Odeint
#SET(Boost_DEBUG 1)
IF (WIN32)
    IF(NOT DEFINED BOOST_ROOT)
        SET(BOOST_ROOT "C:\\Program Files\\boost")
        IF(NOT "$ENV{BOOST_ROOT}" STREQUAL "")
            MESSAGE(STATUS "Use of environnement variable for BOOST")
            SET(BOOST_ROOT $ENV{BOOST_ROOT})
        ENDIF()
    ENDIF()
ENDIF()
MESSAGE(STATUS "BOOST_ROOT : ${BOOST_ROOT}")
SET(Boost_USE_STATIC_LIBS        ON)
IF (NOT(WIN32))
   SET(Boost_USE_MULTITHREADED     OFF)
ENDIF()
#SET(Boost_USE_STATIC_RUNTIME    OFF)
FIND_PACKAGE(Boost 1.53 COMPONENTS program_options REQUIRED)
IF(Boost_FOUND)
    MESSAGE(STATUS "Boost_INCLUDE_DIRS  : ${Boost_INCLUDE_DIRS}")
    MESSAGE(STATUS "Boost_LIBRARIES     : ${Boost_LIBRARIES}")
ENDIF()

SET(YAML_SKIP_INSTALL ON)
ADD_SUBDIRECTORY(yaml-cpp)
SET(YAML_CPP_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp/src
                          ${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp/include
                          ${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp/include/yaml-cpp)

SET(eigen_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/eigen)
ADD_DEFINITIONS(-DEIGEN_DONT_VECTORIZE) # Cf. http://eigen.tuxfamily.org/dox-devel/group__TopicUnalignedArrayAssert.html
ADD_DEFINITIONS(-DEIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT)

if (${CMAKE_BUILD_TYPE})
    if (${CMAKE_BUILD_TYPE} EQUAL Release)
        ADD_DEFINITIONS(-DEIGEN_NO_DEBUG)
    ENDIF()
ENDIF()

#############################################################################
# Compilation part
INCLUDE(CMakeCompilationOptions)
SET(SSC_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../)
ADD_SUBDIRECTORY(exception_handling)
ADD_SUBDIRECTORY(macros)
ADD_SUBDIRECTORY(random_data_generator)
ADD_SUBDIRECTORY(interpolation)
ADD_SUBDIRECTORY(numeric)
ADD_SUBDIRECTORY(text_file_reader)
ADD_SUBDIRECTORY(decode_unit)
ADD_SUBDIRECTORY(data_source)
ADD_SUBDIRECTORY(yaml_parser)
ADD_SUBDIRECTORY(solver)
ADD_SUBDIRECTORY(kinematics)
ADD_SUBDIRECTORY(csv_file_reader)

# Define libraries
add_libs(random_data_generator)
add_libs(exception_handling)
add_libs(yaml_parser)
add_libs(decode_unit)
add_libs(text_file_reader)
add_libs(data_source)
add_libs(kinematics)
add_libs(interpolation)
add_libs(csv_file_reader)
add_libs(numeric)


#############################################################################
# Testing part
ENABLE_TESTING()
IF(BUILD_TESTING)
    SET(BUILDNAME "${BUILDNAME}" CACHE STRING "Name of build on the dashboard")
    MARK_AS_ADVANCED(BUILDNAME)
ENDIF(BUILD_TESTING)

SET(TEST_EXE run_all_tests)

ADD_EXECUTABLE(${TEST_EXE}
        $<TARGET_OBJECTS:random_data_generator_tests>
        $<TARGET_OBJECTS:data_source_tests>
        $<TARGET_OBJECTS:solver_tests>
        $<TARGET_OBJECTS:text_file_reader_tests>
        $<TARGET_OBJECTS:kinematics_tests>
        $<TARGET_OBJECTS:numeric_tests>
        $<TARGET_OBJECTS:csv_file_reader_tests>
        $<TARGET_OBJECTS:interpolation_tests>
        )

TARGET_LINK_LIBRARIES(${TEST_EXE}
        gtest gtest_main
        gmock gmock_main
        ${random_data_generator}_shared
        ${exception_handling}_shared
        ${yaml_parser}_shared
        ${decode_unit}_shared
        ${text_file_reader}_shared
        ${data_source}_shared
        ${kinematics}_shared
        ${csv_file_reader}_shared
        ${interpolation}_shared
        ${numeric}_shared
        lapack
        )

IF(CMAKE_BUILD_TYPE_UPPER MATCHES COVERAGE)
    ENABLE_COVERAGE_REPORT(TARGETS ${TEST_EXE}
                           FILTER boost eigen gmock lapack
                                  /c/mingw/lib/gcc /usr/include)
ENDIF()

#############################################################################
INCLUDE(CMakeCustomTargets)
INCLUDE(CMakePack)

