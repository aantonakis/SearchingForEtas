# Makefile for full Eta code

## VARIABLE DEFINITIONS ##

ETA_SRC_DIR = $(ETAROOT)/src
ETA_INC_DIR = $(ETAROOT)/include
ETA_BUILD_DIR = $(ETAROOT)/build
ETA_LIB_DIR = $(ETAROOT)/lib
ETA_EXECSRC_DIR = $(ETAROOT)/execsrc

LOCAL_INC = -I$(ETA_INC_DIR)
ROOT_INC = `root-config --cflags`

CXXFLAGS = -fPIC $(LOCAL_INC) $(ROOT_INC)

## FILE LISTS ##

#List of source files
SRC_FILES = $(wildcard $(ETA_SRC_DIR)/*.cc)

#List of object files to create
OBJ_FILES = $(patsubst $(ETA_SRC_DIR)/%.cc, $(ETA_BUILD_DIR)/%.o, $(SRC_FILES))

#List of the dependency files for each source file
DEP_FILES = $(patsubst %.o, %.d, $(OBJ_FILES))

## BUILD RULES ##
.PHONY: all src-all lib-all execsrc-all

all: src-all lib-all execsrc-all

src-all: $(OBJ_FILES)

lib-all:
	@$(MAKE) -C $(ETA_LIB_DIR) all

execsrc-all:
	@$(MAKE) -C $(ETA_EXECSRC_DIR) all

#Generic rule for compiling the source code files
# -MMD makes the dependency files (.d files)
# -MP creates dummy make rules to avoid errors if headers are removed
$(ETA_BUILD_DIR)/%.o: $(ETA_SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

#Clean up files. Separate commands for cleaning all files
#and the subdirectories individually
.PHONY: clean src-clean lib-clean execsrc-clean

#clean: src-clean lib-clean util-clean example-clean 
clean: src-clean lib-clean execsrc-clean

src-clean:
	@rm -f $(OBJ_FILES) $(DEP_FILES)

lib-clean:
	@$(MAKE) -C $(ETA_LIB_DIR) clean

execsrc-clean:
	@$(MAKE) -C $(ETA_EXECSRC_DIR) clean

#Include the dependency make files. This system makes sure that a file
#will be recompiled if any of the headers it depends on change.
-include $(DEP_FILES)

