# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/poff/Desktop/Mycoroutine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/poff/Desktop/Mycoroutine

# Include any dependencies generated for this target.
include CMakeFiles/mycoroutine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mycoroutine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mycoroutine.dir/flags.make

CMakeFiles/mycoroutine.dir/src/fiber.cpp.o: CMakeFiles/mycoroutine.dir/flags.make
CMakeFiles/mycoroutine.dir/src/fiber.cpp.o: src/fiber.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/poff/Desktop/Mycoroutine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mycoroutine.dir/src/fiber.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mycoroutine.dir/src/fiber.cpp.o -c /home/poff/Desktop/Mycoroutine/src/fiber.cpp

CMakeFiles/mycoroutine.dir/src/fiber.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mycoroutine.dir/src/fiber.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/poff/Desktop/Mycoroutine/src/fiber.cpp > CMakeFiles/mycoroutine.dir/src/fiber.cpp.i

CMakeFiles/mycoroutine.dir/src/fiber.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mycoroutine.dir/src/fiber.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/poff/Desktop/Mycoroutine/src/fiber.cpp -o CMakeFiles/mycoroutine.dir/src/fiber.cpp.s

CMakeFiles/mycoroutine.dir/src/thread.cpp.o: CMakeFiles/mycoroutine.dir/flags.make
CMakeFiles/mycoroutine.dir/src/thread.cpp.o: src/thread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/poff/Desktop/Mycoroutine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mycoroutine.dir/src/thread.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mycoroutine.dir/src/thread.cpp.o -c /home/poff/Desktop/Mycoroutine/src/thread.cpp

CMakeFiles/mycoroutine.dir/src/thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mycoroutine.dir/src/thread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/poff/Desktop/Mycoroutine/src/thread.cpp > CMakeFiles/mycoroutine.dir/src/thread.cpp.i

CMakeFiles/mycoroutine.dir/src/thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mycoroutine.dir/src/thread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/poff/Desktop/Mycoroutine/src/thread.cpp -o CMakeFiles/mycoroutine.dir/src/thread.cpp.s

# Object files for target mycoroutine
mycoroutine_OBJECTS = \
"CMakeFiles/mycoroutine.dir/src/fiber.cpp.o" \
"CMakeFiles/mycoroutine.dir/src/thread.cpp.o"

# External object files for target mycoroutine
mycoroutine_EXTERNAL_OBJECTS =

lib/libmycoroutine.so: CMakeFiles/mycoroutine.dir/src/fiber.cpp.o
lib/libmycoroutine.so: CMakeFiles/mycoroutine.dir/src/thread.cpp.o
lib/libmycoroutine.so: CMakeFiles/mycoroutine.dir/build.make
lib/libmycoroutine.so: CMakeFiles/mycoroutine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/poff/Desktop/Mycoroutine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library lib/libmycoroutine.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mycoroutine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mycoroutine.dir/build: lib/libmycoroutine.so

.PHONY : CMakeFiles/mycoroutine.dir/build

CMakeFiles/mycoroutine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mycoroutine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mycoroutine.dir/clean

CMakeFiles/mycoroutine.dir/depend:
	cd /home/poff/Desktop/Mycoroutine && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/poff/Desktop/Mycoroutine /home/poff/Desktop/Mycoroutine /home/poff/Desktop/Mycoroutine /home/poff/Desktop/Mycoroutine /home/poff/Desktop/Mycoroutine/CMakeFiles/mycoroutine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mycoroutine.dir/depend

