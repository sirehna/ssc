# Install the dependencies of the program
IF(MINGW)
    # Caution: No cross-compiling is taken into account:
    # If we use a 32 bit compiler, we will get a 32 executable.
    # The same for 64 bit platform
    IF(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
        SET(PLATFORM_ABI x64)
    ELSE()
        SET(PLATFORM_ABI x86)
    ENDIF()
    # 2 Check the exception mechanism
    GET_FILENAME_COMPONENT(MINGW_BIN_PATH ${CMAKE_CXX_COMPILER} PATH)
    MESSAGE(STATUS "MINGW BIN PATH = ${MINGW_BIN_PATH}")
    SET(MINGW_LIB_DIRECTORY "")
    IF(${PLATFORM_ABI} MATCHES "x64")
        SET(MINGW_LIB_DIRECTORY "x86_64-w64-mingw32")
    ELSE()
        SET(MINGW_LIB_DIRECTORY "i686-w64-mingw32")
    ENDIF()
    IF(EXISTS "${MINGW_BIN_PATH}/../${MINGW_LIB_DIRECTORY}/")
        FILE(GLOB MINGW_DLLS ${MINGW_BIN_PATH}/../${MINGW_LIB_DIRECTORY}/lib/*.dll)
    ELSE()
        # Maybe Dlls are present in the mingw bin directory
        FILE(GLOB MINGW_DLLS ${MINGW_BIN_PATH}/*.dll)
    ENDIF()
    FOREACH(f ${MINGW_ADDITIONAL_LIB})
        IF(EXISTS ${f})
            MESSAGE(STATUS "MINGW DLL will be installed = ${f}")
            INSTALL(FILES ${f} DESTINATION ${LIBRARY_OUTPUT_DIRECTORY})
        ENDIF()
    ENDFOREACH()
ENDIF()

SET(PACKAGE_NAME ${PROJECT_NAME})

IF(NOT WIN32) # Otherwise installs headers in /usr instead of /usr/local under Debian
    SET(CPACK_SET_DESTDIR true)
ENDIF()

#####################################"
# Instructions to build an installer
# See http://www.cmake.org/Wiki/CMake:CPackPackageGenerators
SET(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_NAME})

IF(UNIX OR MINGW)
    INCLUDE(InstallRequiredSystemLibraries)
    SET(CPACK_PACKAGE_NAME ${PACKAGE_NAME})
    SET(CPACK_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION OFF)
    SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Sirehna's Scientific Computing Framework")
    SET(CPACK_PACKAGE_VENDOR "SIREHNA")
    SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_BINARY_DIR}/readme.txt")
    SET(CPACK_PACKAGE_VERSION_MAJOR 8)
    SET(CPACK_PACKAGE_VERSION_MINOR 0)
    SET(CPACK_PACKAGE_VERSION_PATCH 3)
    STRING(REGEX REPLACE "(_.*)" "" CPACK_PACKAGE_VERSION_PATCH ${CPACK_PACKAGE_VERSION_PATCH})
    SET(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
    SET(CPACK_COMPONENT_INCLUDE_TOPLEVEL_DIRECTORY OFF)
    SET(CPACK_PACKAGE_FILE_NAME "${PACKAGE_NAME}")
    IF(WIN32)
        # There is a bug in NSIS that does not handle full unix paths properly. Make
        # sure there is at least one set of four (4) backlasshes.
        SET(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\ssc.bmp")
        SET(CPACK_NSIS_INSTALLED_ICON_NAME "${PACKAGE_NAME}-setup")
        SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY}")
        SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.sirehna.com")
        SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.sirehna.com")
        SET(CPACK_NSIS_CONTACT "charles-edouard.cady@sirehna.com")
        SET(CPACK_NSIS_MODIFY_PATH ON)
    ELSE()
        IF(NOT CPACK_GENERATOR)
            SET(CPACK_GENERATOR "DEB")
        ENDIF(NOT CPACK_GENERATOR)
        SET(CPACK_STRIP_FILES "./${PACKAGE_NAME}-setup")
        SET(CPACK_SOURCE_STRIP_FILES "")
        SET(CPACK_PACKAGE_EXECUTABLES "" "")

        CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/linux/deb/postinst.in
                       ${CMAKE_CURRENT_BINARY_DIR}/postinst @ONLY IMMEDIATE)
        FILE(COPY ${CMAKE_CURRENT_BINARY_DIR}/postinst
             DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
             FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
        CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/linux/deb/prerm.in
                       ${CMAKE_CURRENT_BINARY_DIR}/prerm @ONLY IMMEDIATE)
        FILE(COPY ${CMAKE_CURRENT_BINARY_DIR}/prerm
             DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
             FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
        IF(CPACK_GENERATOR STREQUAL "DEB")
            CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/linux/deb/fixup_deb.sh.in
                           ${CMAKE_CURRENT_BINARY_DIR}/fixup_deb.sh @ONLY IMMEDIATE)
            SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Charles-Edouard Cady")
            SET(CPACK_DEBIAN_PACKAGE_NAME ${PROJECT_NAME})
            SET(CPACK_DEBIAN_PACKAGE_VERSION "8.0.3")
            SET(CPACK_DEBIAN_PACKAGE_PRIORITY "")
            SET(CPACK_DEBIAN_PACKAGE_SECTION "")#input our section
            SET(CPACK_DEBIAN_PACKAGE_RECOMMENDS "Unknown")
            SET(CPACK_DEBIAN_PACKAGE_SUGGESTS "Unknown")
            #SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.12), libstdc++6 (>= 4.4.7)")
            #SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "")#i386, amd64
            SET(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_BINARY_DIR}/postinst;${CMAKE_CURRENT_BINARY_DIR}/prerm")
        ENDIF()
    ENDIF()
    INCLUDE(CPack)
ENDIF()

SET(CPACK_COMPONENTS_ALL ${ALL_SSC_COMPONENTS})
INSTALL(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    DESTINATION ${ConfigPackageLocation}
)
INSTALL(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
    DESTINATION ${ConfigPackageLocation}
)
