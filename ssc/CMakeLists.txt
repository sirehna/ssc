CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)
PROJECT(ssc)

SET(CMAKE_VERBOSE_MAKEFILE OFF)

#############################################################################
# CMake utilities
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(CMakeMacros)
#############################################################################

# User configuration
IF(NOT DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug)
ENDIF()

#############################################################################

# GIT SHA
INCLUDE(GetGitRevisionDescription)
GET_GIT_HEAD_REVISION(GIT_REFSPEC GIT_SHA1)

GIT_DESCRIBE(GIT_VERSION --tags --dirty=-dirty)
IF(${GIT_VERSION} STREQUAL "GIT_UNTAGGED_REVISION")
    MESSAGE(STATUS "GIT : Untagged working revision")
    SET(GIT_VERSION_MAJOR 0)
    SET(GIT_VERSION_MINOR 0)
    SET(GIT_VERSION_PATCH 0)
    SET(GIT_VERSION_SHORT ${GIT_SHA1})
    GIT_IS_DIRTY(GIT_VERSION_DIRTY)
ELSE()
    #parse the version information into pieces.
    MESSAGE(STATUS "GIT_VERSION :  ${GIT_VERSION}")
    STRING(REGEX REPLACE "^v([0-9]+)\\..*" "\\1" GIT_VERSION_MAJOR "${GIT_VERSION}")
    STRING(REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" GIT_VERSION_MINOR "${GIT_VERSION}")
    STRING(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" GIT_VERSION_PATCH "${GIT_VERSION}")
    STRING(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.[0-9]+-(.*)" "\\1" GIT_VERSION_SHA1 "${GIT_VERSION}")
    STRING(REGEX MATCH   "^v[0-9]+\\.[0-9]+.*(-dirty)" "\\1" GIT_VERSION_DIRTY "${GIT_VERSION}")
    SET(GIT_VERSION_SHORT "${GIT_VERSION_MAJOR}.${GIT_VERSION_MINOR}.${GIT_VERSION_PATCH}")
    MESSAGE(STATUS "GIT_VERSION_DIRTY ${GIT_VERSION_DIRTY}")
    MESSAGE(STATUS "GIT_VERSION_SHA1 ${GIT_VERSION_SHA1}")
    IF(GIT_VERSION_SHA1)
        SET(GIT_VERSION_SHORT "${GIT_VERSION_SHORT}-${GIT_VERSION_SHA1}")
        IF(NOT ${GIT_VERSION} STREQUAL ${GIT_VERSION_SHA1})
            SET(GIT_VERSION_PATCH "${GIT_VERSION_PATCH}_${GIT_VERSION_SHA1}")
        ENDIF()
    ENDIF()
ENDIF()
IF(${GIT_VERSION_DIRTY})
    SET(GIT_VERSION_SHORT "${GIT_VERSION_SHORT}_dirty")
ENDIF()
SET(${PROJECT_NAME}_MAJOR_VERSION ${GIT_VERSION_MAJOR})
SET(${PROJECT_NAME}_MINOR_VERSION ${GIT_VERSION_MINOR})
SET(${PROJECT_NAME}_PATCH_VERSION ${GIT_VERSION_PATCH})

get_copyright(COPYRIGHT_NOTICE)
STRING(REGEX REPLACE "\\n" " " ${COPYRIGHT_NOTICE} ${COPYRIGHT_NOTICE})

FILE(WRITE  ${CMAKE_CURRENT_BINARY_DIR}/readme.txt.in "@DESCRIPTION@\n")
FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/readme.txt.in "\n")
FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/readme.txt.in "@COPYRIGHT_NOTICE@\n")
FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/readme.txt.in "\n")
FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/readme.txt.in "ID : @GIT_VERSION_SHORT@\n")

FILE(READ "${CMAKE_CURRENT_SOURCE_DIR}/description.txt" DESCRIPTION)
CONFIGURE_FILE(${CMAKE_CURRENT_BINARY_DIR}/readme.txt.in
               ${CMAKE_CURRENT_BINARY_DIR}/readme.txt @ONLY)
#############################################################################
MESSAGE(STATUS "VERSION_MAJOR : ${${PROJECT_NAME}_MAJOR_VERSION}")
MESSAGE(STATUS "VERSION_MINOR : ${${PROJECT_NAME}_MINOR_VERSION}")
MESSAGE(STATUS "VERSION_PATCH : ${${PROJECT_NAME}_PATCH_VERSION}")
SET(${PROJECT_NAME}_VERSION
    ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_VERSION})
SET(${PROJECT_NAME}_VERSION_STR
    ${${PROJECT_NAME}_MAJOR_VERSION}-${${PROJECT_NAME}_MINOR_VERSION}-${${PROJECT_NAME}_PATCH_VERSION})
#############################################################################

get_short_git_hash(short_hash)
write_sha_checker(${short_hash} ${GIT_SHA1} ${${PROJECT_NAME}_MAJOR_VERSION} ${${PROJECT_NAME}_MINOR_VERSION} "check_ssc_version.hpp")

# Configure the package
IF(MINGW)
    SET(ssc_INCLUDE_DIRS "\${CMAKE_CURRENT_LIST_DIR}/../../../include")
ELSE()
    SET(ssc_INCLUDE_DIRS ${CMAKE_INSTALL_PREFIX}/include)
ENDIF()
MESSAGE(STATUS "ssc_INCLUDE_DIRS :${ssc_INCLUDE_DIRS}")
MESSAGE(STATUS "CMAKE_INSTALL_PREFIX :${CMAKE_INSTALL_PREFIX}")
SET(SSC_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../)

INCLUDE(CMakePackageConfigHelpers)
SET(ConfigPackageLocation lib/${PROJECT_NAME}/cmake)
CONFIGURE_PACKAGE_CONFIG_FILE(
       ssc-config.cmake.in
       "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
       INSTALL_DESTINATION "${ConfigPackageLocation}"
       PATH_VARS SSC_INCLUDE_DIRS)
#############################################################################
INCLUDE(CMakeGMock)

INCLUDE(CMakeOutputDirectories)
#############################################################################
# Third party libraries
# Boost
# -> Require at least version 1.53 of boost to use Odeint
#SET(Boost_DEBUG 1)
IF(WIN32)
    IF(NOT DEFINED BOOST_ROOT)
        SET(BOOST_ROOT "C:\\Program Files\\boost")
        IF(NOT "$ENV{BOOST_ROOT}" STREQUAL "")
            MESSAGE(STATUS "Use of environnement variable for BOOST")
            SET(BOOST_ROOT $ENV{BOOST_ROOT})
        ENDIF()
    ENDIF()
ENDIF()
MESSAGE(STATUS "BOOST_ROOT : ${BOOST_ROOT}")
SET(Boost_USE_STATIC_LIBS       ON)
SET(Boost_USE_MULTITHREADED     ON)
#SET(Boost_USE_MULTITHREADED     OFF)
#SET(Boost_USE_STATIC_RUNTIME   OFF)
FIND_PACKAGE(Boost 1.53 COMPONENTS system thread random chrono REQUIRED)
IF(Boost_FOUND)
    MESSAGE(STATUS "Boost_INCLUDE_DIRS    : ${Boost_INCLUDE_DIRS}")
    MESSAGE(STATUS "Boost_LIBRARIES       : ${Boost_LIBRARIES}")
ENDIF()

SET(YAML_SKIP_INSTALL ON)
ADD_SUBDIRECTORY(yaml-cpp)
SET(YAML_CPP_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp/src
    ${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp/include/yaml-cpp
    )

SET(eigen_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/eigen)
# Cf. http://eigen.tuxfamily.org/dox-devel/group__TopicUnalignedArrayAssert.html
ADD_DEFINITIONS(-DEIGEN_DONT_VECTORIZE)
ADD_DEFINITIONS(-DEIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT)
IF(${CMAKE_BUILD_TYPE})
    IF(${CMAKE_BUILD_TYPE} EQUAL Release)
        ADD_DEFINITIONS(-DEIGEN_NO_DEBUG)
    ENDIF()
ENDIF()

ADD_SUBDIRECTORY(f2c)

ADD_SUBDIRECTORY(geographiclib EXCLUDE_FROM_ALL)
SET(geographiclib_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/geographiclib/include
    CACHE PATH "Path to libGeographic include directory")

FIND_PACKAGE(IPOPT REQUIRED)


#############################################################################
# Compilation part
INCLUDE(CMakeCompilationOptions)

# Define libraries
get_copyright(copyright)
add_headers(macros "${copyright}")
add_headers(pimpl_idiom "${copyright}")
add_libs(random_data_generator)
add_libs(exception_handling)
add_libs(decode_unit)
add_libs(yaml_parser
         SSC_DEPENDENCIES decode_unit
         OBJECTS_DEPENDENCIES yaml-cpp_object)
add_libs(text_file_reader
         SSC_DEPENDENCIES exception_handling)

add_libs(integrate
         SSC_DEPENDENCIES exception_handling
         OBJECTS_DEPENDENCIES f2c_object)

add_libs(numeric)
add_libs(data_source
         SSC_DEPENDENCIES exception_handling numeric)
add_libs(kinematics
         SSC_DEPENDENCIES exception_handling data_source)
add_libs(interpolation
         SSC_DEPENDENCIES exception_handling
         OBJECTS_DEPENDENCIES f2c_object)
add_libs(geometry
         OBJECTS_DEPENDENCIES Geographic_object
         SSC_DEPENDENCIES exception_handling interpolation)
add_libs(csv_file_reader
         SSC_DEPENDENCIES exception_handling)
add_libs(csv_writer
         SSC_DEPENDENCIES exception_handling)
add_libs(matrix_and_vector_classes
         SSC_DEPENDENCIES exception_handling)
add_libs(functors_for_optimizer
         SSC_DEPENDENCIES exception_handling interpolation)
add_libs(optimizer
         SSC_DEPENDENCIES exception_handling functors_for_optimizer matrix_and_vector_classes)
add_libs(ipopt_interface
         SSC_DEPENDENCIES exception_handling functors_for_optimizer matrix_and_vector_classes optimizer
         EXTERNAL_DEPENDENCIES ${IPOPT_LIB_DYNAMIC}
         EXTERNAL_DEPENDENCIES_STATIC ${IPOPT_LIB_STATIC})
add_headers(solver "${copyright}")

add_libs(json "${copyright}"
         SSC_DEPENDENCIES exception_handling
         )
INSTALL( DIRECTORY json/rapidjson DESTINATION include/ssc/json )
SET(websocketpp_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/websocketpp)

SET(websocketpp_LIBRARIES
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_RANDOM_LIBRARY}
    ${Boost_CHRONO_LIBRARY}
    )

IF(MINGW)
    add_libs(websocket
        SSC_DEPENDENCIES exception_handling
        EXTERNAL_DEPENDENCIES wsock32 ws2_32
        EXTERNAL_DEPENDENCIES_STATIC ${websocketpp_LIBRARIES})
ELSE()
    add_libs(websocket
            SSC_DEPENDENCIES exception_handling
            EXTERNAL_DEPENDENCIES_STATIC ${websocketpp_LIBRARIES})
ENDIF()

MESSAGE(STATUS "Configuring static library ${name}")
ADD_LIBRARY(ssc_static_no_deps STATIC
    $<TARGET_OBJECTS:random_data_generator_object>
    $<TARGET_OBJECTS:exception_handling_object>
    $<TARGET_OBJECTS:decode_unit_object>
    $<TARGET_OBJECTS:yaml_parser_object>
    $<TARGET_OBJECTS:text_file_reader_object>
    $<TARGET_OBJECTS:integrate_object>
    $<TARGET_OBJECTS:numeric_object>
    $<TARGET_OBJECTS:data_source_object>
    $<TARGET_OBJECTS:kinematics_object>
    $<TARGET_OBJECTS:interpolation_object>
    $<TARGET_OBJECTS:geometry_object>
    $<TARGET_OBJECTS:csv_file_reader_object>
    $<TARGET_OBJECTS:csv_writer_object>
    $<TARGET_OBJECTS:matrix_and_vector_classes_object>
    $<TARGET_OBJECTS:functors_for_optimizer_object>
    $<TARGET_OBJECTS:optimizer_object>
    $<TARGET_OBJECTS:ipopt_interface_object>
    $<TARGET_OBJECTS:websocket_object>
    $<TARGET_OBJECTS:yaml-cpp_object>
    $<TARGET_OBJECTS:f2c_object>
    $<TARGET_OBJECTS:Geographic_object>
    $<TARGET_OBJECTS:json_object>
    )

TARGET_LINK_LIBRARIES(ssc_static_no_deps PRIVATE
    ${IPOPT_LIB_STATIC}
    ${websocketpp_LIBRARIES}
    gfortran
    quadmath # Ipopt
    -static-libgcc
    -static-libstdc++
    )

IF(MINGW)
    TARGET_LINK_LIBRARIES(ssc_static_no_deps PUBLIC wsock32 ws2_32)
ELSE()
    TARGET_LINK_LIBRARIES(ssc_static_no_deps PRIVATE dl) # Ipopt
ENDIF()

SET(AR ${CMAKE_AR})

ADD_CUSTOM_TARGET(ssc_static ALL
    COMMENT "Creates an archive that contains all static libraries"
    COMMAND ${CMAKE_COMMAND} -E remove -f libssc_static.a
    COMMAND ${AR} crT libssc_static.a $<TARGET_FILE:ssc_static_no_deps> ${IPOPT_LIB_STATIC} ${websocketpp_LIBRARIES} && cat ${CMAKE_CURRENT_SOURCE_DIR}/convert_thin_archive_to_normal_one.mri | ${AR} -M
    )

INSTALL(FILES ${CMAKE_BINARY_DIR}/libssc_static.a
        DESTINATION ${LIBRARY_OUTPUT_DIRECTORY}
        COMPONENT ssc)

INSTALL(TARGETS ${ALL_SSC_TARGETS} EXPORT ${PROJECT_NAME}Targets
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
    $<TARGET_OBJECTS:integrate_tests>
    $<TARGET_OBJECTS:text_file_reader_tests>
    $<TARGET_OBJECTS:kinematics_tests>
    $<TARGET_OBJECTS:numeric_tests>
    $<TARGET_OBJECTS:csv_file_reader_tests>
    $<TARGET_OBJECTS:csv_writer_tests>
    $<TARGET_OBJECTS:interpolation_tests>
    $<TARGET_OBJECTS:functors_for_optimizer_tests>
    $<TARGET_OBJECTS:geometry_tests>
    $<TARGET_OBJECTS:matrix_and_vector_classes_tests>
    $<TARGET_OBJECTS:optimizer_tests>
    $<TARGET_OBJECTS:websocket_tests>
    $<TARGET_OBJECTS:ipopt_interface_tests>
    )

TARGET_LINK_LIBRARIES(${TEST_EXE}
    gtest gtest_main
    gmock gmock_main
    ssc_static_no_deps
    )

IF (MINGW)
    TARGET_LINK_LIBRARIES(${TEST_EXE} wsock32 ws2_32)
ELSE()
    TARGET_LINK_LIBRARIES(${TEST_EXE} rt)
ENDIF()

INSTALL(TARGETS ${TEST_EXE}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

STRING(TOUPPER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_UPPER)
IF(${CMAKE_BUILD_TYPE_UPPER} STREQUAL "COVERAGE")
    MESSAGE(STATUS "Adding coverage")
    FIND_PACKAGE(codecov)
    add_coverage(${TEST_EXE})
ENDIF()

#############################################################################
INCLUDE(CMakeCustomTargets)
INCLUDE(CMakePack)
