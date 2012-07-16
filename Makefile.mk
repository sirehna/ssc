BASE_DIR = ../..

include ../Makefile.com

INC = -I inc\
      $(TEST_MACROS_INC)\
      $(EXCEPTION_HANDLING_INC)

LIBS = $(EXCEPTION_HANDLING)
	  
OUTPUT = $(call make_dyn_name,$(MATRIX_AND_VECTOR_CLASSES))

