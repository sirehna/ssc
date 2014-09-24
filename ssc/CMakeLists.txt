CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)
PROJECT(ssc)

SET(CMAKE_VERBOSE_MAKEFILE OFF)

SET(${PROJECT_NAME}_MAJOR_VERSION 1)
SET(${PROJECT_NAME}_MINOR_VERSION 0)
SET(${PROJECT_NAME}_PATCH_VERSION 0)
SET(${PROJECT_NAME}_VERSION
  ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_VERSION})
SET(${PROJECT_NAME}_VERSION_STR
  ${${PROJECT_NAME}_MAJOR_VERSION}-${${PROJECT_NAME}_MINOR_VERSION}-${${PROJECT_NAME}_PATCH_VERSION})

#############################################################################
# CMake utilities
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(CMakeMacros)
#############################################################################

# Configure the package
IF(INSTALL_PREFIX)
    SET(CMAKE_INSTALL_PREFIX ${INSTALL_PREFIX})
ENDIF()
MESSAGE(STATUS "CMAKE_INSTALL_PREFIX :${CMAKE_INSTALL_PREFIX}")
SET(SSC_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../)
SET(ssc_INCLUDE_DIRS ${CMAKE_INSTALL_PREFIX}/include/ssc/${ssc_VERSION})
include(CMakePackageConfigHelpers)
set(ConfigPackageLocation lib/${PROJECT_NAME}-${${PROJECT_NAME}_VERSION_STR}/cmake)

configure_package_config_file ( 
       ssc-config.cmake.in 
       "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
       INSTALL_DESTINATION "${ConfigPackageLocation}"
       PATH_VARS SSC_INCLUDE_DIRS )


SET(CMAKE_VERBOSE_MAKEFILE OFF)
#############################################################################
# User configuration
IF(NOT DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug)
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
FIND_PACKAGE(Boost 1.53 REQUIRED)
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

ADD_SUBDIRECTORY(f2c)
#############################################################################
# Compilation part
INCLUDE(CMakeCompilationOptions)

# Define libraries
add_headers(macros)
add_libs(random_data_generator)
add_libs(exception_handling)
add_libs(yaml_parser
         OBJECT_DEPENDENCIES yaml-cpp_object)
add_libs(decode_unit)
add_libs(text_file_reader
         SSC_DEPENDENCIES exception_handling)
add_libs(numeric)
add_libs(data_source
         SSC_DEPENDENCIES exception_handling numeric)
add_libs(kinematics
         SSC_DEPENDENCIES exception_handling data_source)
add_libs(interpolation
         SSC_DEPENDENCIES exception_handling
         OBJECTS_DEPENDENCIES f2c_object)
add_libs(csv_file_reader ssc_exception_handling)
add_headers(solver)
#LIST(APPEND ALL_SSC_TARGETS f2c)

install(TARGETS ${ALL_SSC_TARGETS} EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

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
        random_data_generator_shared
        exception_handling_shared
        yaml_parser_shared
        decode_unit_shared
        text_file_reader_shared
        data_source_shared
        kinematics_shared
        csv_file_reader_shared
        interpolation_shared
        numeric_shared
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

