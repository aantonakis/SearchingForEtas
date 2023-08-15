# Makefile for JADE shared libraries

## VARIABLE DEFINITIONS ##

ETA_SRC_DIR = $(ETAROOT)/src
ETA_INC_DIR = $(ETAROOT)/include
ETA_LIB_DIR = $(ETAROOT)/lib

LOCAL_INC = -I$(ETA_INC_DIR)

ROOT_INC = `root-config --cflags`
ROOT_LIBS = `root-config --glibs`
ROOT_LDFLAGS = `root-config --ldflags`


CXXFLAGS = -fPIC -shared $(LOCAL_INC) $(ROOT_INC) 
LDLIBS = $(ROOT_LIBS)
LDFLAGS = $(ROOT_LDFLAGS)

## FILE LISTS ##

PREFIXES = Event Slice EventBuilder PrimaryPFP SecondaryPFP
SRC_FILES = $(patsubst %, $(ETA_SRC_DIR)/%.cc, $(PREFIXES)) 
DICT_FILES = $(patsubst %, %Dict.cc, $(PREFIXES)) 

#CONFIG_FILE = $(ETA_SRC_DIR)/Configuration.cc

#Prevent the dictionaries from be deleted by make because they
#are intermediate files in the build process. We may want to look
#at the dictionaries later.
.PRECIOUS: $(DICT_FILES)

## BUILD RULES ##
.PHONY: all

all: libETA.so

# The ETA library should be compiled with the Configuration.cc source as well
libETA.so: $(DICT_FILES) $(SRC_FILES) 
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(LDFLAGS) -o $@ $^
	
%Dict.cc: %Sel.xml $(ETA_INC_DIR)/%.h
	genreflex -s $^ -o $@ --rootmap $*.rootmap -rootmap-lib libETA.so

#Clean up all the libraries and files that genreflex makes
.PHONY: clean

clean:
	@rm -f *.so *Dict.cc *.pcm *.rootmap

