# ------8<---[LINES TO MODIFY WHEN CHANGING MODULE]----->8-----
set(MODULE_UNDER_TEST text_file_reader)
project (${MODULE_UNDER_TEST}_tests)
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

# yaml-cpp includes induce an error when used with the gtest ones ("regex_t does not name a type")
ADD_DEFINITIONS("-DGTEST_HAS_POSIX_RE=0")

ADD_DEFINITIONS("-DPATH_TO_ACCEPTANCE_TESTS=${PATH_TO_ACCEPTANCE_TESTS}")

ADD_DEPENDENCIES(${PROJECT_NAME} googlemock)