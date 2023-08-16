# SearchingForEtas
Analysis Framework for Eta Production in SBND


**SearchingForEtas**

To use this installation of SearchingForEtas, you need to have sourced ROOT 6 

Anytime you want to write a ROOT macro which uses the ETA data structure, you will need to load the ETA library which can be accomplished by adding the following line

`R__LOAD_LIBRARY(libETA.so)`

to the top of your macro. The example macros in the ETA `example/` directory demonstrate how to load various elements of the data structure.

**Building SearchingForEtas**

`env.sh` sets up the ETA environment. Modify it to have appropriate paths for your installation. Then source `env.sh` and run `make` to build SearchingForEtas.

**ETA Source Code**

Source code is in the following directories:

| Directory | Description |
|---------|---------|
| `src/` | Implementation Files (`.cc` source code files) |
| `include/` | Header Files (`.h` source code files) |
| `execsrc/` | Executable Source Code (code intended to be run by users) |

The source code is compiled into the `build/` directory.

Executable source is compiled into the `bin/` directory which is added to the `PATH` variable by the `env.sh` environment script. This makes it so the executable source files can be called from anywhere.

The ETA data structure headers are turned into ROOT dictionaries which are then compiled into a shared library (`libETA.so`) in the `lib/` directory. The `.xml` files in this directory are used to make the selections when creating the ROOT dictionaries with `genreflex`. Load the `libETA.so` library to use SearchingForEtas in root macros. 


