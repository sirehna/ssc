
GCOV_LNK =
# --coverage -lgcov
GCOV_CC =
# -fprofile-arcs -ftest-coverage --coverage

OBJ_DIR = bin/$(PLATFORM)

all: $(OUTPUT_DYN) $(OUTPUT_LIB) TEST

TEST:
	cd unit_tests && make -f Makefile.$(TRGT)

$(OUTPUT_DYN) : $(OBJ_FILES)
	$(CPP) -Wl -shared -o $(OUTPUT_DYN) $(OBJ_FILES) $(GCOV_LNK)

$(OUTPUT_LIB) : $(OBJ_FILES)
	ar rcs $(OUTPUT_LIB) $(OBJ_FILES)
	
$(OBJ_DIR)/%$(OBJ_EXT) : %.cpp %.hpp
	$(CPP) $(INC) $(CFLAGS) $(AYATOLA) -c $< $(OPTIMIZATION) $(MULTI_THREAD_COMPILING) -o $@ $(GCOV_CC)

$(OBJ_DIR)/%$(OBJ_EXT) : %.c %.h
	$(CPP) $(INC) $(CFLAGS) -c $< $(OPTIMIZATION) $(MULTI_THREAD_COMPILING) -o $@ $(GCOV_CC)
	
clean:
	rm -f $(OBJ_DIR)/* && cd unit_tests && make -f Makefile.$(TRGT) clean
