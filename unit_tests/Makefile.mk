BASE_DIR = ../../..

include ../../Makefile.com

INC = $(GOOGLE_TEST_INC)\
      -I inc/\
      -I ../inc/\
      $(RANDOM_DATA_GENERATOR_INC)\
      $(EXCEPTION_HANDLING_INC)\
      $(TEST_MACROS_INC)

LIBS = $(MATRIX_AND_VECTOR_CLASSES)\
       $(RANDOM_DATA_GENERATOR)\
       $(EXCEPTION_HANDLING)


