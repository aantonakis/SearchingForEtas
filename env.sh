# This script sources the relevant stuff for running SearchingForEtas
# You will need to update the paths for your system
# You should also change the compiler to match your system

export CXX=g++
#export CXX=clang++

# Tell the code what directory we're in
export ETAROOT=/Users/alexanderantonakis/Desktop/Eta_Production/SearchingForEtas_GIT/SearchingForEtas


# Add the SearchingForEtas bin directory to the executable search path
export PATH=$ETAROOT/bin:$PATH

# For ROOT 6, genreflex requires headers to be in the ROOT_INCLUDE_PATH
export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$ETAROOT/include/

# Add the shared libraries we build to the library path
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$JADEROOT/lib/

# For Mac OS X
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$ETAROOT/lib/




