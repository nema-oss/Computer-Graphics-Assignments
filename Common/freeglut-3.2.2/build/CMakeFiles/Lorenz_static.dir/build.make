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
include CMakeFiles/Lorenz_static.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Lorenz_static.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Lorenz_static.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lorenz_static.dir/flags.make

CMakeFiles/Lorenz_static.dir/progs/demos/Lorenz/lorenz.c.o: CMakeFiles/Lorenz_static.dir/flags.make
CMakeFiles/Lorenz_static.dir/progs/demos/Lorenz/lorenz.c.o: ../progs/demos/Lorenz/lorenz.c
CMakeFiles/Lorenz_static.dir/progs/demos/Lorenz/lorenz.c.o: CMakeFiles/Lorenz_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nema/DevOgl/Common/freeglut-3.2.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Lorenz_static.dir/progs/demos/Lorenz/lorenz.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Lorenz_static.dir/progs/demos/Lorenz/lorenz.c.o -MF CMakeFiles/Lorenz_static.dir/progs/demos/Lorenz/lorenz.c.o.d -o CMakeFiles/Lorenz_static.dir/progs/demos/Lorenz/lorenz.c.o -c /home/nema/DevOgl/Common/freeglut-3.2.2/progs/demos/Lorenz/lorenz.c

CMakeFiles/Lorenz_static.dir/progs/demos/Lorenz/lorenz.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Lorenz_static.dir/progs/demos/Lorenz/lorenz.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/nema/DevOgl/Common/freeglut-3.2.2/progs/demos/Lorenz/lorenz.c > CMakeFiles/Lorenz_static.dir/progs/demos/Lorenz/lorenz.c.i

CMakeFiles/Lorenz_static.dir/progs/demos/Lorenz/lorenz.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Lorenz_static.dir/progs/demos/Lorenz/lorenz.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/nema/DevOgl/Common/freeglut-3.2.2/progs/demos/Lorenz/lorenz.c -o CMakeFiles/Lorenz_static.dir/progs/demos/Lorenz/lorenz.c.s

# Object files for target Lorenz_static
Lorenz_static_OBJECTS = \
"CMakeFiles/Lorenz_static.dir/progs/demos/Lorenz/lorenz.c.o"

# External object files for target Lorenz_static
Lorenz_static_EXTERNAL_OBJECTS =

bin/Lorenz_static: CMakeFiles/Lorenz_static.dir/progs/demos/Lorenz/lorenz.c.o
bin/Lorenz_static: CMakeFiles/Lorenz_static.dir/build.make
bin/Lorenz_static: /usr/lib64/libGLU.so
bin/Lorenz_static: /usr/lib64/libGL.so
bin/Lorenz_static: /usr/lib64/libX11.so
bin/Lorenz_static: /usr/lib64/libXrandr.so
bin/Lorenz_static: /usr/lib64/libXi.so
bin/Lorenz_static: lib/libglut.a
bin/Lorenz_static: /usr/lib64/libGL.so
bin/Lorenz_static: /usr/lib64/libX11.so
bin/Lorenz_static: /usr/lib64/libXrandr.so
bin/Lorenz_static: /usr/lib64/libXi.so
bin/Lorenz_static: CMakeFiles/Lorenz_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nema/DevOgl/Common/freeglut-3.2.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/Lorenz_static"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lorenz_static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lorenz_static.dir/build: bin/Lorenz_static
.PHONY : CMakeFiles/Lorenz_static.dir/build

CMakeFiles/Lorenz_static.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lorenz_static.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lorenz_static.dir/clean

CMakeFiles/Lorenz_static.dir/depend:
	cd /home/nema/DevOgl/Common/freeglut-3.2.2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nema/DevOgl/Common/freeglut-3.2.2 /home/nema/DevOgl/Common/freeglut-3.2.2 /home/nema/DevOgl/Common/freeglut-3.2.2/build /home/nema/DevOgl/Common/freeglut-3.2.2/build /home/nema/DevOgl/Common/freeglut-3.2.2/build/CMakeFiles/Lorenz_static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Lorenz_static.dir/depend

