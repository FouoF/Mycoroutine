# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/poff/Desktop/Mycoroutine/CMakeFiles /home/poff/Desktop/Mycoroutine/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/poff/Desktop/Mycoroutine/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named test

# Build rule for target.
test: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test
.PHONY : test

# fast build rule for target.
test/fast:
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/build
.PHONY : test/fast

#=============================================================================
# Target rules for targets named mycoroutine

# Build rule for target.
mycoroutine: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 mycoroutine
.PHONY : mycoroutine

# fast build rule for target.
mycoroutine/fast:
	$(MAKE) -f CMakeFiles/mycoroutine.dir/build.make CMakeFiles/mycoroutine.dir/build
.PHONY : mycoroutine/fast

src/fiber.o: src/fiber.cpp.o

.PHONY : src/fiber.o

# target to build an object file
src/fiber.cpp.o:
	$(MAKE) -f CMakeFiles/mycoroutine.dir/build.make CMakeFiles/mycoroutine.dir/src/fiber.cpp.o
.PHONY : src/fiber.cpp.o

src/fiber.i: src/fiber.cpp.i

.PHONY : src/fiber.i

# target to preprocess a source file
src/fiber.cpp.i:
	$(MAKE) -f CMakeFiles/mycoroutine.dir/build.make CMakeFiles/mycoroutine.dir/src/fiber.cpp.i
.PHONY : src/fiber.cpp.i

src/fiber.s: src/fiber.cpp.s

.PHONY : src/fiber.s

# target to generate assembly for a file
src/fiber.cpp.s:
	$(MAKE) -f CMakeFiles/mycoroutine.dir/build.make CMakeFiles/mycoroutine.dir/src/fiber.cpp.s
.PHONY : src/fiber.cpp.s

src/scheduler.o: src/scheduler.cpp.o

.PHONY : src/scheduler.o

# target to build an object file
src/scheduler.cpp.o:
	$(MAKE) -f CMakeFiles/mycoroutine.dir/build.make CMakeFiles/mycoroutine.dir/src/scheduler.cpp.o
.PHONY : src/scheduler.cpp.o

src/scheduler.i: src/scheduler.cpp.i

.PHONY : src/scheduler.i

# target to preprocess a source file
src/scheduler.cpp.i:
	$(MAKE) -f CMakeFiles/mycoroutine.dir/build.make CMakeFiles/mycoroutine.dir/src/scheduler.cpp.i
.PHONY : src/scheduler.cpp.i

src/scheduler.s: src/scheduler.cpp.s

.PHONY : src/scheduler.s

# target to generate assembly for a file
src/scheduler.cpp.s:
	$(MAKE) -f CMakeFiles/mycoroutine.dir/build.make CMakeFiles/mycoroutine.dir/src/scheduler.cpp.s
.PHONY : src/scheduler.cpp.s

src/thread.o: src/thread.cpp.o

.PHONY : src/thread.o

# target to build an object file
src/thread.cpp.o:
	$(MAKE) -f CMakeFiles/mycoroutine.dir/build.make CMakeFiles/mycoroutine.dir/src/thread.cpp.o
.PHONY : src/thread.cpp.o

src/thread.i: src/thread.cpp.i

.PHONY : src/thread.i

# target to preprocess a source file
src/thread.cpp.i:
	$(MAKE) -f CMakeFiles/mycoroutine.dir/build.make CMakeFiles/mycoroutine.dir/src/thread.cpp.i
.PHONY : src/thread.cpp.i

src/thread.s: src/thread.cpp.s

.PHONY : src/thread.s

# target to generate assembly for a file
src/thread.cpp.s:
	$(MAKE) -f CMakeFiles/mycoroutine.dir/build.make CMakeFiles/mycoroutine.dir/src/thread.cpp.s
.PHONY : src/thread.cpp.s

tests/test.o: tests/test.cpp.o

.PHONY : tests/test.o

# target to build an object file
tests/test.cpp.o:
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/tests/test.cpp.o
.PHONY : tests/test.cpp.o

tests/test.i: tests/test.cpp.i

.PHONY : tests/test.i

# target to preprocess a source file
tests/test.cpp.i:
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/tests/test.cpp.i
.PHONY : tests/test.cpp.i

tests/test.s: tests/test.cpp.s

.PHONY : tests/test.s

# target to generate assembly for a file
tests/test.cpp.s:
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/tests/test.cpp.s
.PHONY : tests/test.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... test"
	@echo "... mycoroutine"
	@echo "... src/fiber.o"
	@echo "... src/fiber.i"
	@echo "... src/fiber.s"
	@echo "... src/scheduler.o"
	@echo "... src/scheduler.i"
	@echo "... src/scheduler.s"
	@echo "... src/thread.o"
	@echo "... src/thread.i"
	@echo "... src/thread.s"
	@echo "... tests/test.o"
	@echo "... tests/test.i"
	@echo "... tests/test.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

