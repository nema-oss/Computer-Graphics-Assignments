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
include CMakeFiles/DVA338_Lab1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/DVA338_Lab1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/DVA338_Lab1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DVA338_Lab1.dir/flags.make

CMakeFiles/DVA338_Lab1.dir/main.cpp.o: CMakeFiles/DVA338_Lab1.dir/flags.make
CMakeFiles/DVA338_Lab1.dir/main.cpp.o: ../main.cpp
CMakeFiles/DVA338_Lab1.dir/main.cpp.o: CMakeFiles/DVA338_Lab1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nema/DevOgl/DVA338_Lab1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DVA338_Lab1.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DVA338_Lab1.dir/main.cpp.o -MF CMakeFiles/DVA338_Lab1.dir/main.cpp.o.d -o CMakeFiles/DVA338_Lab1.dir/main.cpp.o -c /home/nema/DevOgl/DVA338_Lab1/main.cpp

CMakeFiles/DVA338_Lab1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DVA338_Lab1.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nema/DevOgl/DVA338_Lab1/main.cpp > CMakeFiles/DVA338_Lab1.dir/main.cpp.i

CMakeFiles/DVA338_Lab1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DVA338_Lab1.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nema/DevOgl/DVA338_Lab1/main.cpp -o CMakeFiles/DVA338_Lab1.dir/main.cpp.s

CMakeFiles/DVA338_Lab1.dir/shaders.cpp.o: CMakeFiles/DVA338_Lab1.dir/flags.make
CMakeFiles/DVA338_Lab1.dir/shaders.cpp.o: ../shaders.cpp
CMakeFiles/DVA338_Lab1.dir/shaders.cpp.o: CMakeFiles/DVA338_Lab1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nema/DevOgl/DVA338_Lab1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/DVA338_Lab1.dir/shaders.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DVA338_Lab1.dir/shaders.cpp.o -MF CMakeFiles/DVA338_Lab1.dir/shaders.cpp.o.d -o CMakeFiles/DVA338_Lab1.dir/shaders.cpp.o -c /home/nema/DevOgl/DVA338_Lab1/shaders.cpp

CMakeFiles/DVA338_Lab1.dir/shaders.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DVA338_Lab1.dir/shaders.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nema/DevOgl/DVA338_Lab1/shaders.cpp > CMakeFiles/DVA338_Lab1.dir/shaders.cpp.i

CMakeFiles/DVA338_Lab1.dir/shaders.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DVA338_Lab1.dir/shaders.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nema/DevOgl/DVA338_Lab1/shaders.cpp -o CMakeFiles/DVA338_Lab1.dir/shaders.cpp.s

# Object files for target DVA338_Lab1
DVA338_Lab1_OBJECTS = \
"CMakeFiles/DVA338_Lab1.dir/main.cpp.o" \
"CMakeFiles/DVA338_Lab1.dir/shaders.cpp.o"

# External object files for target DVA338_Lab1
DVA338_Lab1_EXTERNAL_OBJECTS =

DVA338_Lab1: CMakeFiles/DVA338_Lab1.dir/main.cpp.o
DVA338_Lab1: CMakeFiles/DVA338_Lab1.dir/shaders.cpp.o
DVA338_Lab1: CMakeFiles/DVA338_Lab1.dir/build.make
DVA338_Lab1: /usr/lib64/libOpenGL.so
DVA338_Lab1: /usr/lib64/libGLX.so
DVA338_Lab1: /usr/lib64/libGLU.so
DVA338_Lab1: /usr/lib64/libGLEW.so
DVA338_Lab1: /usr/lib64/libGLEW.so
DVA338_Lab1: liblib_algebra.a
DVA338_Lab1: liblib_camera.a
DVA338_Lab1: liblib_mesh.a
DVA338_Lab1: ../test/prebuilds/Release/camera_tests.lib
DVA338_Lab1: ../test/prebuilds/Release/math_tests.lib
DVA338_Lab1: CMakeFiles/DVA338_Lab1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nema/DevOgl/DVA338_Lab1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable DVA338_Lab1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DVA338_Lab1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DVA338_Lab1.dir/build: DVA338_Lab1
.PHONY : CMakeFiles/DVA338_Lab1.dir/build

CMakeFiles/DVA338_Lab1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DVA338_Lab1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DVA338_Lab1.dir/clean

CMakeFiles/DVA338_Lab1.dir/depend:
	cd /home/nema/DevOgl/DVA338_Lab1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nema/DevOgl/DVA338_Lab1 /home/nema/DevOgl/DVA338_Lab1 /home/nema/DevOgl/DVA338_Lab1/build /home/nema/DevOgl/DVA338_Lab1/build /home/nema/DevOgl/DVA338_Lab1/build/CMakeFiles/DVA338_Lab1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DVA338_Lab1.dir/depend

