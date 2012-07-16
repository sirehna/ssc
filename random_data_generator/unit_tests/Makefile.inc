OBJ_DIR = bin/$(PLATFORM)

TEST_EXE = $(OBJ_DIR)/run_all_tests

all: $(TEST_EXE)

$(TEST_EXE) : $(OBJ_FILES) $(LIBS)
	$(CPP) -o $(TEST_EXE) $(OBJ_FILES) $(LIBS) $(GCOV_LNK) -lpthread

$(OBJ_DIR)/%$(OBJ_EXT) : %.cpp %.hpp
	$(CPP) $(INC) $(CFLAGS) -c $< $(OPTIMIZATION) -o $@  -DTEST_VIRTUAL=virtual $(GCOV_CC)

clean:
	rm -f $(OBJ_DIR)/*
