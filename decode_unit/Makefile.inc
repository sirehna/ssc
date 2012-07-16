all: $(OBJ_DIR)/$(OUTPUT_LIB) $(LAPACK_LIB)

$(LAPACK_LIB):
	cd source/lapack && make -f Makefile.$(TRGT) && cd ..

$(OBJ_DIR)/$(OUTPUT_LIB): $(OBJ_FILES) $(LAPACK_LIB)
	g++ -Wall -D_JNI_IMPLEMENTATION_ -Wl -shared -o $(OBJ_DIR)/$(OUTPUT_LIB) $(OBJ_FILES)  $(LAPACK_LIB) -lstdc++

$(OBJ_DIR)/%$(OBJ_EXT) : %.cpp %.hpp
	$(CPP) $(INC) $(CFLAGS) -DNDEBUG -c $< $(OPTIMIZATION) -o $@

$(OBJ_DIR)/%$(OBJ_EXT) : %.cpp
	$(CPP) $(INC) $(CFLAGS) -g3 -gdwarf-2 -DNDEBUG -c $< $(OPTIMIZATION) -o $@

clean:
	rm -f $(OBJ_DIR)/*
