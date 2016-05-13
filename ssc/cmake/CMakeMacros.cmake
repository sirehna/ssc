# This file contains CMake macros, that can be called in CMakeLists.txt file

# This macro produces a string containing the time of the call to this macro
MACRO(MACRO_TODAY TODAY_RESULT)
    SET(${TODAY_RESULT} YYYYY mm DD -- HH MM)
    IF(UNIX OR MSYS)
        EXECUTE_PROCESS(COMMAND "date" "+%Y_%m_%d__%H_%M" OUTPUT_VARIABLE ${TODAY_RESULT} OUTPUT_STRIP_TRAILING_WHITESPACE)
        # Trick to get rid of eol characters
        STRING(REGEX REPLACE "(....)_(..)_(..)__(..)_(..).*" "\\1 \\2 \\3 -- \\4 \\5" ${TODAY_RESULT} ${${TODAY_RESULT}})
    ELSEIF(WIN32)
        EXECUTE_PROCESS(COMMAND "cmd" " /C date /T && time /T" OUTPUT_VARIABLE ${TODAY_RESULT} OUTPUT_STRIP_TRAILING_WHITESPACE)
        # MESSAGE(STATUS "TODAY_RESULT = ${${TODAY_RESULT}}")
        # Trick to get rid of eol characters
        STRING(REGEX REPLACE "(..)/(..)/(....).*(..):(..).*" "\\3 \\2 \\1 -- \\4 \\5" ${TODAY_RESULT} ${${TODAY_RESULT}})
    ELSE()
        MESSAGE(SEND_ERROR "Date not implemented")
    ENDIF()
ENDMACRO(MACRO_TODAY)

MACRO(MACRO_SVNVERSION SVNVERSION_RESULT)
    FIND_PACKAGE(Subversion)
    SET(${SVNVERSION_RESULT} "Repertoire_non_versionne_avec_SVN")
    FIND_PROGRAM(SVNVERSION_EXECUTABLE svnversion)
    IF(SVNVERSION_EXECUTABLE)
        EXECUTE_PROCESS(COMMAND "${SVNVERSION_EXECUTABLE}" "${PROJECT_SOURCE_DIR}" OUTPUT_VARIABLE ${SVNVERSION_RESULT} OUTPUT_STRIP_TRAILING_WHITESPACE)
        STRING(REPLACE ":" "_" ${SVNVERSION_RESULT} ${${SVNVERSION_RESULT}})
    ENDIF()
ENDMACRO(MACRO_SVNVERSION)

FUNCTION(_Boost_COMPILER_DUMPVERSION _OUTPUT_VERSION)
    EXEC_PROGRAM(${CMAKE_CXX_COMPILER}
        ARGS ${CMAKE_CXX_COMPILER_ARG1} -dumpversion
        OUTPUT_VARIABLE _boost_COMPILER_VERSION
    )
    STRING(REGEX REPLACE "([0-9])\\.([0-9])(\\.[0-9])?" "\\1\\2"
        _boost_COMPILER_VERSION ${_boost_COMPILER_VERSION})

    SET(${_OUTPUT_VERSION} ${_boost_COMPILER_VERSION} PARENT_SCOPE)
ENDFUNCTION()

FUNCTION(GET_BUILD_TYPE_STR DBG_STR)
    IF(CMAKE_BUILD_TYPE MATCHES Debug)
        SET(${DBG_STR} debug PARENT_SCOPE)
    ELSE()
        SET(${DBG_STR} release PARENT_SCOPE)
    ENDIF()
ENDFUNCTION()

FUNCTION(ARCHITECTURE ARCHSTR)
    # Test 32/64 bits
    IF("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
        SET(${ARCHSTR} "64bits" PARENT_SCOPE)
    ELSE("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
        SET(${ARCHSTR} "32bits" PARENT_SCOPE)
    ENDIF()
ENDFUNCTION()

# Guesses Boost's compiler prefix used in built library names
# Returns the guess by setting the variable pointed to by _ret
FUNCTION(GUESS_COMPILER_PREFIX _ret)
    IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel"
        OR "${CMAKE_CXX_COMPILER}" MATCHES "icl"
        OR "${CMAKE_CXX_COMPILER}" MATCHES "icpc")
        IF(WIN32)
            SET(_boost_COMPILER "iw")
        ELSE()
            SET(_boost_COMPILER "il")
        ENDIF()
    ELSEIF(MSVC12)
        SET(_boost_COMPILER "vc120")
    ELSEIF(MSVC11)
        SET(_boost_COMPILER "vc110")
    ELSEIF(MSVC10)
        SET(_boost_COMPILER "vc100")
    ELSEIF(MSVC90)
        SET(_boost_COMPILER "vc90")
    ELSEIF(MSVC80)
        SET(_boost_COMPILER "vc80")
    ELSEIF(MSVC71)
        SET(_boost_COMPILER "vc71")
    ELSEIF(MSVC70) # Good luck!
        SET(_boost_COMPILER "vc7") # yes, this is correct
    ELSEIF(MSVC60) # Good luck!
        SET(_boost_COMPILER "vc6") # yes, this is correct
    ELSEIF(BORLAND)
        SET(_boost_COMPILER "bcb")
    ELSEIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "SunPro")
        SET(_boost_COMPILER "sw")
    ELSEIF(MINGW)
        _Boost_COMPILER_DUMPVERSION(_boost_COMPILER_VERSION)
        SET(_boost_COMPILER "mgw${_boost_COMPILER_VERSION}")
    ELSEIF(UNIX)
        IF(CMAKE_COMPILER_IS_GNUCXX)
            _Boost_COMPILER_DUMPVERSION(_boost_COMPILER_VERSION)
            # Determine which version of GCC we have.
            SET(_boost_COMPILER "gcc-${_boost_COMPILER_VERSION}")
        ENDIF()
    ELSE()
        # TODO at least Boost_DEBUG here?
        SET(_boost_COMPILER "")
    ENDIF()
    SET(${_ret} ${_boost_COMPILER} PARENT_SCOPE)
ENDFUNCTION()

FUNCTION(GET_LIBNAME LIBNAME VERSIONSTR OUT)
    _Boost_COMPILER_DUMPVERSION(test)
    GUESS_COMPILER_PREFIX(COMPILERSTR)
    GET_BUILD_TYPE_STR(DBG_STR)
    ARCHITECTURE(ARCHSTR)
    SET(SYSTEM ${CMAKE_SYSTEM_NAME}-${ARCHSTR})
    #SET(${OUT} ${LIBNAME}-${SYSTEM}-${COMPILERSTR}-${DBG_STR}-${VERSIONSTR} PARENT_SCOPE)
    SET(${OUT} ${LIBNAME} PARENT_SCOPE)
ENDFUNCTION()

#At the end of this script snippet, the CMake variable PROCESSOR_COUNT has a
#value appropriate for passing to make's -j for parallel builds.
#
#When used in a ctest -S script, you can call...
#
#IF(PROCESSOR_COUNT)
#  SET(CTEST_BUILD_FLAGS "-j${PROCESSOR_COUNT}")
#ENDIF()
#
#...to enable parallel builds with "Unix Makefiles" and the ctest_build
#command.
MACRO(MACRO_GET_NUMBER_OF_PROCESSORS PROCESSOR_COUNT)
    # Unknown:
    SET(PROCESSOR_COUNT 0)
    # Linux:
    SET(cpuinfo_file "/proc/cpuinfo")
    IF(EXISTS "${cpuinfo_file}")
        FILE(STRINGS "${cpuinfo_file}" procs REGEX "^processor.: [0-9]+$")
        LIST(LENGTH procs PROCESSOR_COUNT)
    ENDIF()
    # Mac:
    IF(APPLE)
        FIND_PROGRAM(cmd_sys_pro "system_profiler")
        IF(cmd_sys_pro)
            EXECUTE_PROCESS(COMMAND ${cmd_sys_pro} OUTPUT_VARIABLE info)
            STRING(REGEX REPLACE "^.*Total Number Of Cores: ([0-9]+).*$" "\\1"
                   PROCESSOR_COUNT "${info}")
        ENDIF()
    ENDIF()
    # Windows:
    IF(WIN32)
        SET(PROCESSOR_COUNT "$ENV{NUMBER_OF_PROCESSORS}")
    ENDIF()
ENDMACRO(MACRO_GET_NUMBER_OF_PROCESSORS)

MACRO(create_wrapper_hpp module_name headers copyright)
    SET(${module_name}_INCLUDES_ "")
    FOREACH(f ${headers})
        GET_FILENAME_COMPONENT(x ${f} NAME)
        LIST(APPEND ${module_name}_INCLUDES_ "#include \"ssc/${module_name}/${x}\"")
        LIST(APPEND ${module_name}_INCLUDES_ "\n")
    ENDFOREACH()
    STRING(REPLACE ";" "" ${module_name}_INCLUDES "${${module_name}_INCLUDES_}")
    SET(COPYRIGHT_NOTICE ${copyright})
    FILE(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.hpp.in "")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.hpp.in "/*")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.hpp.in "@COPYRIGHT_NOTICE@")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.hpp.in "*/")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.hpp.in "\n")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.hpp.in "#ifndef ${module_name}_guard\n")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.hpp.in "#define ${module_name}_guard\n")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.hpp.in "\n")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.hpp.in "@${module_name}_INCLUDES@\n")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.hpp.in "\n")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.hpp.in "#endif")
    CONFIGURE_FILE(${CMAKE_CURRENT_BINARY_DIR}/${module_name}.hpp.in ${module_name}.hpp)
ENDMACRO()

MACRO(append_copyright IN_FILE OUT_FILE copyright)
    FILE(READ ${IN_FILE} CONTENTS)
    FILE(WRITE ${OUT_FILE} "/*")
    FILE(APPEND ${OUT_FILE} ${copyright})
    FILE(APPEND ${OUT_FILE} "*/")
    FILE(APPEND ${OUT_FILE} "${CONTENTS}")
ENDMACRO()

MACRO(append_copyright_and_install module_name header copyright)
    get_filename_component(b ${header} NAME)
    append_copyright(${header} ${CMAKE_CURRENT_BINARY_DIR}/${module_name}/${b} ${copyright})
    INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/${module_name}/${b}
            DESTINATION include/ssc/${module_name}
            COMPONENT ${module_name}
            )
ENDMACRO()

MACRO(add_headers name copyright)
    ADD_SUBDIRECTORY(${name})
    FILE(GLOB headers ${name}/*.h*)
    FOREACH(header ${headers})
        append_copyright_and_install(${name} ${header} ${copyright})
    ENDFOREACH()
    create_wrapper_hpp(${name} "${headers}" "${copyright}")
    INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/${name}.hpp
            DESTINATION include/ssc
            COMPONENT ${name}
            )

    LIST(APPEND ALL_SSC_COMPONENTS ${name})
ENDMACRO()

MACRO(get_copyright copyright)
    FILE(READ "${CMAKE_CURRENT_SOURCE_DIR}/copyright_notice.txt" ${copyright})
ENDMACRO()

MACRO(add_libs name)
    SET(multiValueArgs SSC_DEPENDENCIES EXTERNAL_DEPENDENCIES EXTERNAL_DEPENDENCIES_STATIC OBJECTS_DEPENDENCIES)
    cmake_parse_arguments(add_libs "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    get_copyright(copyright)
    add_headers(${name} "${copyright}")
    GET_LIBNAME("ssc_${name}" ${${PROJECT_NAME}_VERSION_STR} ${name})
    # Dynamic library
    MESSAGE(STATUS "Configuring dynamic library ${name}")
    IF(add_libs_OBJECTS_DEPENDENCIES)
        ADD_LIBRARY(${name}_shared SHARED
                    $<TARGET_OBJECTS:${name}_object>
                    $<TARGET_OBJECTS:${add_libs_OBJECTS_DEPENDENCIES}>
                    )
    ELSE()
        ADD_LIBRARY(${name}_shared SHARED
                    $<TARGET_OBJECTS:${name}_object>
                    )
    ENDIF()
    SET_TARGET_PROPERTIES(${name}_shared PROPERTIES OUTPUT_NAME ${${name}}_shared)
    LIST(APPEND ALL_SSC_TARGETS ${name}_shared)
    FOREACH(f ${add_libs_SSC_DEPENDENCIES})
        SET(current_arg_name ${f})
        TARGET_LINK_LIBRARIES(${name}_shared PUBLIC ${current_arg_name}_shared)
    ENDFOREACH()
    TARGET_LINK_LIBRARIES(${name}_shared  PRIVATE ${add_libs_EXTERNAL_DEPENDENCIES_STATIC})
    TARGET_LINK_LIBRARIES(${name}_shared  PRIVATE ${add_libs_EXTERNAL_DEPENDENCIES})
    INSTALL(TARGETS ${name}_shared
            RUNTIME DESTINATION ${RUNTIME_OUTPUT_DIRECTORY}
            LIBRARY DESTINATION ${LIBRARY_OUTPUT_DIRECTORY}
            ARCHIVE DESTINATION ${LIBRARY_OUTPUT_DIRECTORY}
            COMPONENT ${name}
    )

    # Static library
    IF(add_libs_EXTERNAL_DEPENDENCIES_STATIC)
        MESSAGE(STATUS "Configuring static library ${name} with static dependencies")
        ADD_LIBRARY(${name}_static2 STATIC
                    $<TARGET_OBJECTS:${name}_object>
                    )
        SET_TARGET_PROPERTIES(${name}_static2 PROPERTIES OUTPUT_NAME ${${name}}_static2)
        # LIST(APPEND ALL_SSC_TARGETS ${name}_static)
        FOREACH(f ${add_libs_SSC_DEPENDENCIES})
            SET(current_arg_name ${f})
            TARGET_LINK_LIBRARIES(${name}_static2 PUBLIC ${current_arg_name}_static2)
        ENDFOREACH()
        TARGET_LINK_LIBRARIES(${name}_static2 PRIVATE ${add_libs_EXTERNAL_DEPENDENCIES})
        # TODO : Improved this part of the code maybe with CMAKE_CXX_ARCHIVE_CREATE
        # WARNING : This part of the code works only on Linux environment (MinGW included)
        ADD_CUSTOM_TARGET(${name}_static ALL
            COMMENT "Creates an archive that contains all static libraries"
            COMMAND ${CMAKE_COMMAND} -E remove -f libssc_${name}_static.a
            COMMAND ${CMAKE_AR} qc libssc_${name}_static.a $<TARGET_FILE:${name}_static2> ${add_libs_EXTERNAL_DEPENDENCIES_STATIC})
        SET_TARGET_PROPERTIES(${name}_static PROPERTIES OUTPUT_NAME ${${name}}_static)
        # INSTALL(TARGETS ${name}_static EXPORT ${PROJECT_NAME}Targets
        INSTALL(FILES ${CMAKE_BINARY_DIR}/libssc_${name}_static.a
                DESTINATION ${LIBRARY_OUTPUT_DIRECTORY}
                COMPONENT ${name})
    ELSE()
        MESSAGE(STATUS "Configuring static library ${name}")
        ADD_LIBRARY(${name}_static STATIC
                    $<TARGET_OBJECTS:${name}_object>
                    )
        SET_TARGET_PROPERTIES(${name}_static PROPERTIES OUTPUT_NAME ${${name}}_static)
        LIST(APPEND ALL_SSC_TARGETS ${name}_static)
        FOREACH(f ${add_libs_SSC_DEPENDENCIES})
            SET(current_arg_name ${f})
            TARGET_LINK_LIBRARIES(${name}_static PUBLIC ${current_arg_name}_static)
        ENDFOREACH()
        TARGET_LINK_LIBRARIES(${name}_static PRIVATE ${add_libs_EXTERNAL_DEPENDENCIES})
        INSTALL(TARGETS ${name}_static
                RUNTIME DESTINATION ${RUNTIME_OUTPUT_DIRECTORY}
                LIBRARY DESTINATION ${LIBRARY_OUTPUT_DIRECTORY}
                ARCHIVE DESTINATION ${LIBRARY_OUTPUT_DIRECTORY}
                COMPONENT ${name}
        )
    ENDIF()
ENDMACRO()

MACRO(write_sha_checker short_sha long_sha major minor filename)
    FILE(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${filename} "")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${filename} "#ifndef SSC_SHA_CHECKER\n")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${filename} "#define SSC_SHA_CHECKER\n")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${filename} "\n")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${filename} "#include <boost/static_assert.hpp>\n\n")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${filename} "#define SSC_GIT_SHA 0x${short_sha}\n\n")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${filename} "#define LONG_SSC_GIT_SHA \"0x${long_sha}\"\n\n")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${filename} "// Compile-time assert. Usage: CHECK_SSC_SHA(0x741957727bb3e14);\n")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${filename} "#define CHECK_SSC_SHA(expected) BOOST_STATIC_ASSERT(SSC_GIT_SHA == expected);\n\n")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${filename} "// Compile-time assert. Usage: CHECK_SSC_VERSION(4,5,3);\n")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${filename} "#define CHECK_SSC_VERSION(X,Y) BOOST_STATIC_ASSERT(X == ${major});BOOST_STATIC_ASSERT(Y>=${minor});\n\n")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${filename} "#endif")
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${filename} "\n")
    INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/${filename}
            DESTINATION include/ssc
            )
ENDMACRO()
