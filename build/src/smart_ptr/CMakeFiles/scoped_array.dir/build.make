# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lwh/code/CppPearlPick

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lwh/code/CppPearlPick/build

# Include any dependencies generated for this target.
include src/smart_ptr/CMakeFiles/scoped_array.dir/depend.make

# Include the progress variables for this target.
include src/smart_ptr/CMakeFiles/scoped_array.dir/progress.make

# Include the compile flags for this target's objects.
include src/smart_ptr/CMakeFiles/scoped_array.dir/flags.make

src/smart_ptr/CMakeFiles/scoped_array.dir/scoped_array.cpp.o: src/smart_ptr/CMakeFiles/scoped_array.dir/flags.make
src/smart_ptr/CMakeFiles/scoped_array.dir/scoped_array.cpp.o: ../src/smart_ptr/scoped_array.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lwh/code/CppPearlPick/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/smart_ptr/CMakeFiles/scoped_array.dir/scoped_array.cpp.o"
	cd /home/lwh/code/CppPearlPick/build/src/smart_ptr && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/scoped_array.dir/scoped_array.cpp.o -c /home/lwh/code/CppPearlPick/src/smart_ptr/scoped_array.cpp

src/smart_ptr/CMakeFiles/scoped_array.dir/scoped_array.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/scoped_array.dir/scoped_array.cpp.i"
	cd /home/lwh/code/CppPearlPick/build/src/smart_ptr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lwh/code/CppPearlPick/src/smart_ptr/scoped_array.cpp > CMakeFiles/scoped_array.dir/scoped_array.cpp.i

src/smart_ptr/CMakeFiles/scoped_array.dir/scoped_array.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/scoped_array.dir/scoped_array.cpp.s"
	cd /home/lwh/code/CppPearlPick/build/src/smart_ptr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lwh/code/CppPearlPick/src/smart_ptr/scoped_array.cpp -o CMakeFiles/scoped_array.dir/scoped_array.cpp.s

src/smart_ptr/CMakeFiles/scoped_array.dir/scoped_array.cpp.o.requires:

.PHONY : src/smart_ptr/CMakeFiles/scoped_array.dir/scoped_array.cpp.o.requires

src/smart_ptr/CMakeFiles/scoped_array.dir/scoped_array.cpp.o.provides: src/smart_ptr/CMakeFiles/scoped_array.dir/scoped_array.cpp.o.requires
	$(MAKE) -f src/smart_ptr/CMakeFiles/scoped_array.dir/build.make src/smart_ptr/CMakeFiles/scoped_array.dir/scoped_array.cpp.o.provides.build
.PHONY : src/smart_ptr/CMakeFiles/scoped_array.dir/scoped_array.cpp.o.provides

src/smart_ptr/CMakeFiles/scoped_array.dir/scoped_array.cpp.o.provides.build: src/smart_ptr/CMakeFiles/scoped_array.dir/scoped_array.cpp.o


# Object files for target scoped_array
scoped_array_OBJECTS = \
"CMakeFiles/scoped_array.dir/scoped_array.cpp.o"

# External object files for target scoped_array
scoped_array_EXTERNAL_OBJECTS =

bin/scoped_array: src/smart_ptr/CMakeFiles/scoped_array.dir/scoped_array.cpp.o
bin/scoped_array: src/smart_ptr/CMakeFiles/scoped_array.dir/build.make
bin/scoped_array: src/smart_ptr/CMakeFiles/scoped_array.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lwh/code/CppPearlPick/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/scoped_array"
	cd /home/lwh/code/CppPearlPick/build/src/smart_ptr && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/scoped_array.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/smart_ptr/CMakeFiles/scoped_array.dir/build: bin/scoped_array

.PHONY : src/smart_ptr/CMakeFiles/scoped_array.dir/build

src/smart_ptr/CMakeFiles/scoped_array.dir/requires: src/smart_ptr/CMakeFiles/scoped_array.dir/scoped_array.cpp.o.requires

.PHONY : src/smart_ptr/CMakeFiles/scoped_array.dir/requires

src/smart_ptr/CMakeFiles/scoped_array.dir/clean:
	cd /home/lwh/code/CppPearlPick/build/src/smart_ptr && $(CMAKE_COMMAND) -P CMakeFiles/scoped_array.dir/cmake_clean.cmake
.PHONY : src/smart_ptr/CMakeFiles/scoped_array.dir/clean

src/smart_ptr/CMakeFiles/scoped_array.dir/depend:
	cd /home/lwh/code/CppPearlPick/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lwh/code/CppPearlPick /home/lwh/code/CppPearlPick/src/smart_ptr /home/lwh/code/CppPearlPick/build /home/lwh/code/CppPearlPick/build/src/smart_ptr /home/lwh/code/CppPearlPick/build/src/smart_ptr/CMakeFiles/scoped_array.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/smart_ptr/CMakeFiles/scoped_array.dir/depend
