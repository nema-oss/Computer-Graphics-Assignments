# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nema/DevOgl/Common/freeglut-3.2.2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nema/DevOgl/Common/freeglut-3.2.2/build

# Include any dependencies generated for this target.
include CMakeFiles/CallbackMaker.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CallbackMaker.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CallbackMaker.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CallbackMaker.dir/flags.make

CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.o: CMakeFiles/CallbackMaker.dir/flags.make
CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.o: ../progs/demos/CallbackMaker/CallbackMaker.c
CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.o: CMakeFiles/CallbackMaker.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nema/DevOgl/Common/freeglut-3.2.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.o -MF CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.o.d -o CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.o -c /home/nema/DevOgl/Common/freeglut-3.2.2/progs/demos/CallbackMaker/CallbackMaker.c

CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/nema/DevOgl/Common/freeglut-3.2.2/progs/demos/CallbackMaker/CallbackMaker.c > CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.i

CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/nema/DevOgl/Common/freeglut-3.2.2/progs/demos/CallbackMaker/CallbackMaker.c -o CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.s

# Object files for target CallbackMaker
CallbackMaker_OBJECTS = \
"CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.o"

# External object files for target CallbackMaker
CallbackMaker_EXTERNAL_OBJECTS =

bin/CallbackMaker: CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.o
bin/CallbackMaker: CMakeFiles/CallbackMaker.dir/build.make
bin/CallbackMaker: /usr/lib64/libGLU.so
bin/CallbackMaker: /usr/lib64/libGL.so
bin/CallbackMaker: /usr/lib64/libX11.so
bin/CallbackMaker: /usr/lib64/libXrandr.so
bin/CallbackMaker: /usr/lib64/libXi.so
bin/CallbackMaker: lib/libglut.so.3.11.1
bin/CallbackMaker: /usr/lib64/libGL.so
bin/CallbackMaker: /usr/lib64/libX11.so
bin/CallbackMaker: /usr/lib64/libXrandr.so
bin/CallbackMaker: /usr/lib64/libXi.so
bin/CallbackMaker: CMakeFiles/CallbackMaker.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nema/DevOgl/Common/freeglut-3.2.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/CallbackMaker"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CallbackMaker.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CallbackMaker.dir/build: bin/CallbackMaker
.PHONY : CMakeFiles/CallbackMaker.dir/build

CMakeFiles/CallbackMaker.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CallbackMaker.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CallbackMaker.dir/clean

CMakeFiles/CallbackMaker.dir/depend:
	cd /home/nema/DevOgl/Common/freeglut-3.2.2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nema/DevOgl/Common/freeglut-3.2.2 /home/nema/DevOgl/Common/freeglut-3.2.2 /home/nema/DevOgl/Common/freeglut-3.2.2/build /home/nema/DevOgl/Common/freeglut-3.2.2/build /home/nema/DevOgl/Common/freeglut-3.2.2/build/CMakeFiles/CallbackMaker.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CallbackMaker.dir/depend

