# Install the dependencies of the program
IF(MSYS)
    GET_FILENAME_COMPONENT(MINGW_BIN_PATH ${CMAKE_CXX_COMPILER} PATH)
    MESSAGE(STATUS "MINGW_BIN_PATH = ${MINGW_BIN_PATH}")
    LIST(APPEND MINGW_ADDITIONAL_LIB "${MINGW_BIN_PATH}/libgcc_s_dw2-1.dll")
    LIST(APPEND MINGW_ADDITIONAL_LIB "${MINGW_BIN_PATH}/libstdc++-6.dll")
    LIST(APPEND MINGW_ADDITIONAL_LIB "${MINGW_BIN_PATH}/libgfortran-3.dll")
    #LIST(APPEND MINGW_ADDITIONAL_LIB "${MINGW_BIN_PATH}/libquadmath-0.dll")
    FOREACH(f ${MINGW_ADDITIONAL_LIB})
        IF(EXISTS ${f})
            INSTALL(FILES ${f} DESTINATION ${LIBRARY_OUTPUT_DIRECTORY})
        ENDIF()
    ENDFOREACH()
ENDIF()

SET(NAME ${PROJECT_NAME}_${${PROJECT_NAME}_VERSION_STR})

#####################################"
# Instructions to build an installer
IF(UNIX OR MSYS)
    INCLUDE(InstallRequiredSystemLibraries)
    SET(CPACK_PACKAGE_NAME ${NAME})
    SET(CPACK_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION OFF)
    SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Framework de calcul scientifique de DCNS Research")
    SET(CPACK_PACKAGE_VENDOR "DCNS Research")
    #SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
    SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_BINARY_DIR}/Copyright.txt")
    SET(CPACK_PACKAGE_VERSION_MAJOR ${${PROJECT_NAME}_MAJOR_VERSION})
    SET(CPACK_PACKAGE_VERSION_MINOR ${${PROJECT_NAME}_MINOR_VERSION})
    SET(CPACK_PACKAGE_VERSION_PATCH ${${PROJECT_NAME}_PATCH_VERSION})
    SET(CPACK_PACKAGE_INSTALL_DIRECTORY "ssc")
    SET(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
    SET(CPACK_COMPONENT_INCLUDE_TOPLEVEL_DIRECTORY OFF)
    IF(WIN32)
        # There is a bug in NSIS that does not handle full unix paths properly. Make
        # sure there is at least one set of four (4) backlasshes.
        SET(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/ssc.bmp")
        SET(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}")
        SET(CPACK_NSIS_INSTALLED_ICON_NAME "${NAME}_setup")
        SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY}")
        SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.sirehna.com")
        SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.sirehna.com")
        SET(CPACK_NSIS_CONTACT "charles-edouard.cady@sirehna.com")
        SET(CPACK_NSIS_MODIFY_PATH ON)
        #SET(CPACK_PACKAGE_EXECUTABLES "" "")
    ELSE(WIN32)
        SET(CPACK_STRIP_FILES "./${NAME}_setup")
        SET(CPACK_SOURCE_STRIP_FILES "")
        SET(CPACK_PACKAGE_EXECUTABLES "" "")
        SET(CPACK_GENERATOR "DEB")
        SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Charles-Edouard Cady")
        ##CPACK_PACKAGING_INSTALL_PREFIX : Sets the default root that the generated package installs into, '/usr' is the default for the debian and redhat generators
        SET(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}")
        #SET(CPACK_PACKAGING_INSTALL_PREFIX "$HOME/ssc")
        ##To generate a RPM file, one needs program rpmbuild that can be
        ##installed with
        ##su
        ##yum install rpm-build
        ##yum install --skip-broken rpm-build
        ##To see the content of a RPM file, use the following command
        ##rpm -q -filesbypkg -p DYSCOASM-0.0.0-Linux.rpm
        ##
        ##rpm -i --prefix=/home/people/jacquenot/simulateurIrtJv/ simulateurIrtJv_installer_1589M.rpm
    ENDIF(WIN32)
    INCLUDE(CPack)
ENDIF(UNIX OR MSYS)
