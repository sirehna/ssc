# ------8<---[LINES TO MODIFY WHEN CHANGING MODULE]----->8-----
set(MODULE_UNDER_TEST random_data_generator)
project (${MODULE_UNDER_TEST}_tests)
FILE(GLOB SRC src/random_data_generator_tests.cpp)
# ------8<---------------------------------------------->8-----

include_directories (inc)
include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})


add_library (${PROJECT_NAME} OBJECT ${SRC})

