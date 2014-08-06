# ------8<---[LINES TO MODIFY WHEN CHANGING MODULE]----->8-----
set(MODULE_UNDER_TEST text_file_reader)
project(${MODULE_UNDER_TEST}_tests)
FILE(GLOB SRC src/TextFileReaderTest.cpp)
# ------8<---------------------------------------------->8-----

# Include directories
include_directories(inc)
include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
include_directories(${${MODULE_UNDER_TEST}_SOURCE_DIR}/inc)
include_directories(${random_data_generator_INCLUDE_DIRS})
include_directories(${validate_using_csv_files_INCLUDE_DIRS})

# Linking libraries
add_library(${PROJECT_NAME} OBJECT ${SRC})

ADD_DEFINITIONS("-DPATH_TO_ACCEPTANCE_TESTS=${PATH_TO_ACCEPTANCE_TESTS}")
