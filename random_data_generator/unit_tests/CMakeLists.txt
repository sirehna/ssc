# ------8<---[LINES TO MODIFY WHEN CHANGING MODULE]----->8-----
set(MODULE_UNDER_TEST random_data_generator)
project (${MODULE_UNDER_TEST}_tests)
FILE(GLOB SRC src/random_data_generator_tests.cpp)
# ------8<---------------------------------------------->8-----

enable_testing()

# Include directories
include_directories (inc)
include_directories(SYSTEM ${GTEST_INCLUDE_DIR})

add_library (${PROJECT_NAME} OBJECT ${SRC})

# Build executable
#add_executable(run_all_tests ${SRC})
#target_link_libraries(run_all_tests ${GTEST_BOTH_LIBRARIES})
#target_link_libraries(run_all_tests ${MODULE_UNDER_TEST}_static)
#
## Register test with CTest
#add_test(all_tests_in_${MODULE_UNDER_TEST} run_all_tests)

