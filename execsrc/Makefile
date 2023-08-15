# Makefile for JADE charge likelihood construction code

## VARIABLE DEFINITIONS ##

ETA_SRC_DIR = $(ETAROOT)/src
ETA_INC_DIR = $(ETAROOT)/include
ETA_BUILD_DIR = $(ETAROOT)/build
ETA_LIB_DIR = $(ETAROOT)/lib
ETA_BIN_DIR = $(ETAROOT)/bin

LOCAL_INC = -I$(ETA_INC_DIR)
#LOCAL_LIBS = -lRecoInfo -lPulseInfo -lEventInfo
LOCAL_LIBS = -lETA
LOCAL_LDFLAGS = -L$(ETA_LIB_DIR)

ROOT_INC = `root-config --cflags`
ROOT_LIBS = `root-config --glibs`
ROOT_LDFLAGS = `root-config --ldflags`


CXXFLAGS = -fPIC $(LOCAL_INC) $(ROOT_INC)
LDLIBS = $(LOCAL_LIBS) $(ROOT_LIBS) 
LDFLAGS = $(LOCAL_LDFLAGS) $(ROOT_LDFLAGS) 

## FILE LISTS ##

# List of source files in this directory
SRC_FILES = $(wildcard *.cc)

# Files to build
TARGET_FILES = $(patsubst %.cc, $(ETA_BIN_DIR)/%, $(SRC_FILES))
OBJ_FILES = $(patsubst %.cc, $(ETA_BIN_DIR)/%.o, $(SRC_FILES))

# Object files from the main source code for linking
ETA_SRC_FILES = $(wildcard $(ETA_SRC_DIR)/*.cc)
ETA_OBJ_FILES = $(patsubst $(ETA_SRC_DIR)/%.cc, $(ETA_BUILD_DIR)/%.o, $(ETA_SRC_FILES))

## BUILD RULES ##

.PHONY: all

# Tell make to get rid of the intermediate .o files even though they are
# prerequisites for the build targets
.INTERMEDIATE: $(OBJ_FILES)

all: $(TARGET_FILES)

# Generic build rule for constructing executables from .cc source files
# Use static pattern rule to allow files to be made individually


#$(OBJDIR)/%.o : $(SRCDIR)/%.c
#        $(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<


$(TARGET_FILES): %: %.o $(ETA_OBJ_FILES)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(ETA_BIN_DIR)/%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $^ -o $@

# Clean up the executables
.PHONY: clean

clean:
	@rm -f $(TARGET_FILES)

