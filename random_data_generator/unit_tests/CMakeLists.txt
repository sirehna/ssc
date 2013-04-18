# ------8<---[LINES TO MODIFY WHEN CHANGING MODULE]----->8-----
set(MODULE_UNDER_TEST random_data_generator)
project (${MODULE_UNDER_TEST}_tests)
FILE(GLOB SRC src/random_data_generator_tests.cpp)
# ------8<---------------------------------------------->8-----

enable_testing()

if (${BUILD_STANDALONE_LIB})
    # Add gmock (recompiled for each module because every user needs to compile his tests using the same compiler flags
    # used to compile the installed Google Mock libraries; otherwise he may run into undefined behaviors. If you compile
    # Google Mock and your test code using different compiler flags, they may see different definitions of the same
    # class/function/variable)
    IF (WIN32)
       set(DISABLE_PTHREADS OFF) # Otherwise doesn't compile on MinGW because of MinGW's non-standard implementation
    ELSE()
       set(DISABLE_PTHREADS ON)
    ENDIF()
    set(GTEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/${GTEST_ROOT})
    find_package(GTest REQUIRED)
endif()

# Include directories
include_directories (inc)
include_directories(SYSTEM ${GTEST_INCLUDE_DIR})


if (${BUILD_STANDALONE_LIB})
    set(TEST_EXE run_all_tests)
    add_executable(${TEST_EXE} src/random_data_generator_tests.cpp
                               $<TARGET_OBJECTS:random_data_generator_static>)
    target_link_libraries(${TEST_EXE} 
                      ${GTEST_BOTH_LIBRARIES}
                      )
else()
    add_library (${PROJECT_NAME} OBJECT SRC)
    ADD_DEPENDENCIES(${PROJECT_NAME} googlemock)
endif()