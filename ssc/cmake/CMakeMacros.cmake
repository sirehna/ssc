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

function(_Boost_COMPILER_DUMPVERSION _OUTPUT_VERSION)

  exec_program(${CMAKE_CXX_COMPILER}
    ARGS ${CMAKE_CXX_COMPILER_ARG1} -dumpversion
    OUTPUT_VARIABLE _boost_COMPILER_VERSION
  )
  string(REGEX REPLACE "([0-9])\\.([0-9])(\\.[0-9])?" "\\1\\2"
    _boost_COMPILER_VERSION ${_boost_COMPILER_VERSION})

  set(${_OUTPUT_VERSION} ${_boost_COMPILER_VERSION} PARENT_SCOPE)
endfunction()

function(GET_BUILD_TYPE_STR DBG_STR)
    if (CMAKE_BUILD_TYPE MATCHES Debug)
        set(${DBG_STR} debug PARENT_SCOPE)
    else()
        set(${DBG_STR} release PARENT_SCOPE)
    endif()
endfunction()

function(ARCHITECTURE ARCHSTR)
    # Test 32/64 bits
    if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
       set(${ARCHSTR} "64bits" PARENT_SCOPE)
    else("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
       set(${ARCHSTR} "32bits" PARENT_SCOPE)
    endif()
endfunction()

# Guesses Boost's compiler prefix used in built library names
# Returns the guess by setting the variable pointed to by _ret
function(GUESS_COMPILER_PREFIX _ret)
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel"
      OR "${CMAKE_CXX_COMPILER}" MATCHES "icl"
      OR "${CMAKE_CXX_COMPILER}" MATCHES "icpc")
    if(WIN32)
      set (_boost_COMPILER "iw")
    else()
      set (_boost_COMPILER "il")
    endif()
  elseif (MSVC12)
    set(_boost_COMPILER "vc120")
  elseif (MSVC11)
    set(_boost_COMPILER "vc110")
  elseif (MSVC10)
    set(_boost_COMPILER "vc100")
  elseif (MSVC90)
    set(_boost_COMPILER "vc90")
  elseif (MSVC80)
    set(_boost_COMPILER "vc80")
  elseif (MSVC71)
    set(_boost_COMPILER "vc71")
  elseif (MSVC70) # Good luck!
    set(_boost_COMPILER "vc7") # yes, this is correct
  elseif (MSVC60) # Good luck!
    set(_boost_COMPILER "vc6") # yes, this is correct
  elseif (BORLAND)
    set(_boost_COMPILER "bcb")
  elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "SunPro")
    set(_boost_COMPILER "sw")
  elseif (MINGW)
      _Boost_COMPILER_DUMPVERSION(_boost_COMPILER_VERSION)
      set(_boost_COMPILER "mgw${_boost_COMPILER_VERSION}")
  elseif (UNIX)
    if (CMAKE_COMPILER_IS_GNUCXX)
        _Boost_COMPILER_DUMPVERSION(_boost_COMPILER_VERSION)
        # Determine which version of GCC we have.
      set(_boost_COMPILER "gcc-${_boost_COMPILER_VERSION}")
    endif ()
  else()
    # TODO at least Boost_DEBUG here?
    set(_boost_COMPILER "")
  endif()
  set(${_ret} ${_boost_COMPILER} PARENT_SCOPE)
endfunction()


function(GET_LIBNAME LIBNAME VERSIONSTR OUT)
_Boost_COMPILER_DUMPVERSION(test)
    GUESS_COMPILER_PREFIX(COMPILERSTR)
    GET_BUILD_TYPE_STR(DBG_STR)
    ARCHITECTURE(ARCHSTR)
    set(SYSTEM ${CMAKE_SYSTEM_NAME}-${ARCHSTR})
    set(${OUT} ${LIBNAME}-${SYSTEM}-${COMPILERSTR}-${DBG_STR}-${VERSIONSTR} PARENT_SCOPE)
endfunction()

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

MACRO(create_wrapper_hpp module_name headers)
    set(${module_name}_INCLUDES "")
    foreach(f ${headers})
        get_filename_component(x ${f} NAME)
        LIST(APPEND ${module_name}_INCLUDES "#include \"ssc/${module_name}/${x}\"")
        LIST(APPEND ${module_name}_INCLUDES "\n")
    endforeach()
    STRING(REGEX REPLACE ";" "" ${module_name}_INCLUDES "${${module_name}_INCLUDES}")
    configure_file(${module_name}.hpp.in ${module_name}.hpp)
ENDMACRO()

MACRO(add_headers name)
    ADD_SUBDIRECTORY(${name})
    FILE(GLOB headers ${name}/*.h*)

    INSTALL(FILES ${headers}
            DESTINATION ssc/${name}
            COMPONENT ${name}
            )
    INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/${name}.hpp
            DESTINATION ssc
            COMPONENT ${name}
            )
    LIST(APPEND ALL_SSC_COMPONENTS ${name})
    create_wrapper_hpp(${name} headers)
ENDMACRO()


MACRO(add_libs name)
    SET(multiValueArgs SSC_DEPENDENCIES EXTERNAL_DEPENDENCIES OBJECTS_DEPENDENCIES)
    cmake_parse_arguments(add_libs "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_headers(${name})
    GET_LIBNAME("ssc_${name}" ${${PROJECT_NAME}_VERSION_STR} ${name})
    ADD_LIBRARY(${name}_static STATIC
                $<TARGET_OBJECTS:${name}_object>
                )
    SET_TARGET_PROPERTIES(${name}_static PROPERTIES OUTPUT_NAME ${${name}}_static)
    LIST(APPEND ALL_SSC_TARGETS ${name}_static)
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
        TARGET_LINK_LIBRARIES(${name}_static ${current_arg_name}_static)
        TARGET_LINK_LIBRARIES(${name}_shared ${current_arg_name}_shared)
    ENDFOREACH()
    FOREACH(f ${add_libs_EXTERNAL_DEPENDENCIES})
        SET(current_arg_name ${f})
        TARGET_LINK_LIBRARIES(${name}_static ${current_arg_name})
        TARGET_LINK_LIBRARIES(${name}_shared ${current_arg_name})
    ENDFOREACH()

    INSTALL(TARGETS ${name}_static ${name}_shared
            RUNTIME DESTINATION ${RUNTIME_OUTPUT_DIRECTORY}
            LIBRARY DESTINATION ${LIBRARY_OUTPUT_DIRECTORY}
            ARCHIVE DESTINATION ${LIBRARY_OUTPUT_DIRECTORY}
            COMPONENT ${name}
    )
ENDMACRO()
