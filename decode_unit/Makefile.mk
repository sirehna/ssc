OBJ_DIR = bin/$(PLATFORM)

vpath %.cpp source
vpath %.hpp include
vpath %.o $(OBJ_DIR)

INC = -I include/ 

OPTIMIZATION = -O3

OBJ_FILES = $(OBJ_DIR)/blowfish_2$(OBJ_EXT)\
            $(OBJ_DIR)/DecodeUnit$(OBJ_EXT)\
            $(OBJ_DIR)/FMArray$(OBJ_EXT)\
            $(OBJ_DIR)/FMCrypto$(OBJ_EXT)\
            $(OBJ_DIR)/FMException$(OBJ_EXT)\
            $(OBJ_DIR)/FMFile$(OBJ_EXT)\
            $(OBJ_DIR)/FMIniFile$(OBJ_EXT)\
            $(OBJ_DIR)/FMLinearAlgebra$(OBJ_EXT)\
            $(OBJ_DIR)/FMList$(OBJ_EXT)\
            $(OBJ_DIR)/FMMatrix_extended$(OBJ_EXT)\
            $(OBJ_DIR)/FMSerialization$(OBJ_EXT)\
            $(OBJ_DIR)/FMSignalReadFredynFile$(OBJ_EXT)\
            $(OBJ_DIR)/FMStats$(OBJ_EXT)\
            $(OBJ_DIR)/FMStream$(OBJ_EXT)\
            $(OBJ_DIR)/FMString$(OBJ_EXT)\
            $(OBJ_DIR)/FMTime$(OBJ_EXT)\
            $(OBJ_DIR)/FMUnitaryTest$(OBJ_EXT)\
            $(OBJ_DIR)/FMVariables$(OBJ_EXT)\
            $(OBJ_DIR)/FMXml$(OBJ_EXT)


.PHONY: all clean debug

OUTPUT_NAME = fm_tools
OUTPUT_LIB = lib$(OUTPUT_NAME)$(DYN_EXT)
