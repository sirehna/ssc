GOOGLE_TEST_DIR = ../../gtest-1.6.0
GOOGLE_TEST_INC = -isystem $(GOOGLE_TEST_DIR)/include/


vpath %.o $(OBJ_DIR)
vpath %.cpp src
vpath %.hpp inc
vpath %.c src
vpath %.h inc

INC = $(GOOGLE_TEST_INC)\
      -I inc/\
      -I ../inc/\
      -I ../../macros

LIBS = ../$(OBJ_DIR)/librandom_data_generator$(DYN_EXT)\
       $(GOOGLE_TEST_LIB)

OBJ_FILES = $(OBJ_DIR)/random_data_generator_tests$(OBJ_EXT)

CPP = g++
WARNING_AS_ERRORS = -Werror -Wfatal-errors
AYATOLA = -Woverloaded-virtual -Weffc++ -pedantic  \
          -pedantic-errors -Wextra  -Wall\
          -Wunused-function  -Wunused-label  -Wunused-parameter \
          -Wunused-value  -Wunused-variable  -Wvariadic-macros

DISABLE_WARNING_FOR_SYSTEM_LIBS = -isystem /usr/include

CFLAGS = $(AYATOLA) $(WARNING_AS_ERRORS) -g


