CPP = g++
WARNING_AS_ERRORS = -Werror -Wfatal-errors
AYATOLA = -Woverloaded-virtual -Weffc++ -pedantic  \
          -pedantic-errors -Wextra  -Wall\
          -Wunused-function  -Wunused-label  -Wunused-parameter \
          -Wunused-value  -Wunused-variable  -Wvariadic-macros

DISABLE_WARNING_FOR_SYSTEM_LIBS = -isystem /usr/include

CFLAGS = $(WARNING_AS_ERRORS) -g

OBJ_DIR = bin/$(PLATFORM)

vpath %.o $(OBJ_DIR)
vpath %.cpp src
vpath %.hpp inc
vpath %.c src
vpath %.h inc

INC = -I inc/\
      -I ../macros

OPTIMIZATION = -O3


OBJ_FILES = $(OBJ_DIR)/DataGenerator$(OBJ_EXT)\
            $(OBJ_DIR)/sir_rand$(OBJ_EXT)

.PHONY: all clean debug


OUTPUT_DYN = $(OBJ_DIR)/librandom_data_generator$(DYN_EXT)
OUTPUT_LIB = $(OBJ_DIR)/librandom_data_generator$(LIB_EXT)

