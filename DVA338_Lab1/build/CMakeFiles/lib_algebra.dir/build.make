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
CMAKE_SOURCE_DIR = /home/nema/DevOgl/DVA338_Lab1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nema/DevOgl/DVA338_Lab1/build

# Include any dependencies generated for this target.
include CMakeFiles/lib_algebra.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lib_algebra.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lib_algebra.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lib_algebra.dir/flags.make

CMakeFiles/lib_algebra.dir/algebra.cpp.o: CMakeFiles/lib_algebra.dir/flags.make
CMakeFiles/lib_algebra.dir/algebra.cpp.o: ../algebra.cpp
CMakeFiles/lib_algebra.dir/algebra.cpp.o: CMakeFiles/lib_algebra.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nema/DevOgl/DVA338_Lab1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lib_algebra.dir/algebra.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lib_algebra.dir/algebra.cpp.o -MF CMakeFiles/lib_algebra.dir/algebra.cpp.o.d -o CMakeFiles/lib_algebra.dir/algebra.cpp.o -c /home/nema/DevOgl/DVA338_Lab1/algebra.cpp

CMakeFiles/lib_algebra.dir/algebra.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_algebra.dir/algebra.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nema/DevOgl/DVA338_Lab1/algebra.cpp > CMakeFiles/lib_algebra.dir/algebra.cpp.i

CMakeFiles/lib_algebra.dir/algebra.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_algebra.dir/algebra.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nema/DevOgl/DVA338_Lab1/algebra.cpp -o CMakeFiles/lib_algebra.dir/algebra.cpp.s

# Object files for target lib_algebra
lib_algebra_OBJECTS = \
"CMakeFiles/lib_algebra.dir/algebra.cpp.o"

# External object files for target lib_algebra
lib_algebra_EXTERNAL_OBJECTS =

liblib_algebra.a: CMakeFiles/lib_algebra.dir/algebra.cpp.o
liblib_algebra.a: CMakeFiles/lib_algebra.dir/build.make
liblib_algebra.a: CMakeFiles/lib_algebra.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nema/DevOgl/DVA338_Lab1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library liblib_algebra.a"
	$(CMAKE_COMMAND) -P CMakeFiles/lib_algebra.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lib_algebra.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lib_algebra.dir/build: liblib_algebra.a
.PHONY : CMakeFiles/lib_algebra.dir/build

CMakeFiles/lib_algebra.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lib_algebra.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lib_algebra.dir/clean

CMakeFiles/lib_algebra.dir/depend:
	cd /home/nema/DevOgl/DVA338_Lab1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nema/DevOgl/DVA338_Lab1 /home/nema/DevOgl/DVA338_Lab1 /home/nema/DevOgl/DVA338_Lab1/build /home/nema/DevOgl/DVA338_Lab1/build /home/nema/DevOgl/DVA338_Lab1/build/CMakeFiles/lib_algebra.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lib_algebra.dir/depend

