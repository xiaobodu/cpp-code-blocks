# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/johnsun/tcprelay

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/johnsun/tcprelay/build/debug

# Include any dependencies generated for this target.
include CMakeFiles/relay.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/relay.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/relay.dir/flags.make

CMakeFiles/relay.dir/tcprelay.cc.o: CMakeFiles/relay.dir/flags.make
CMakeFiles/relay.dir/tcprelay.cc.o: ../../tcprelay.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/johnsun/tcprelay/build/debug/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/relay.dir/tcprelay.cc.o"
	g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/relay.dir/tcprelay.cc.o -c /home/johnsun/tcprelay/tcprelay.cc

CMakeFiles/relay.dir/tcprelay.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/relay.dir/tcprelay.cc.i"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/johnsun/tcprelay/tcprelay.cc > CMakeFiles/relay.dir/tcprelay.cc.i

CMakeFiles/relay.dir/tcprelay.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/relay.dir/tcprelay.cc.s"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/johnsun/tcprelay/tcprelay.cc -o CMakeFiles/relay.dir/tcprelay.cc.s

CMakeFiles/relay.dir/tcprelay.cc.o.requires:
.PHONY : CMakeFiles/relay.dir/tcprelay.cc.o.requires

CMakeFiles/relay.dir/tcprelay.cc.o.provides: CMakeFiles/relay.dir/tcprelay.cc.o.requires
	$(MAKE) -f CMakeFiles/relay.dir/build.make CMakeFiles/relay.dir/tcprelay.cc.o.provides.build
.PHONY : CMakeFiles/relay.dir/tcprelay.cc.o.provides

CMakeFiles/relay.dir/tcprelay.cc.o.provides.build: CMakeFiles/relay.dir/tcprelay.cc.o

# Object files for target relay
relay_OBJECTS = \
"CMakeFiles/relay.dir/tcprelay.cc.o"

# External object files for target relay
relay_EXTERNAL_OBJECTS =

bin/relay: CMakeFiles/relay.dir/tcprelay.cc.o
bin/relay: CMakeFiles/relay.dir/build.make
bin/relay: lib/libencryptor_openssl.a
bin/relay: lib/libmuduo_cdns.a
bin/relay: CMakeFiles/relay.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable bin/relay"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/relay.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/relay.dir/build: bin/relay
.PHONY : CMakeFiles/relay.dir/build

CMakeFiles/relay.dir/requires: CMakeFiles/relay.dir/tcprelay.cc.o.requires
.PHONY : CMakeFiles/relay.dir/requires

CMakeFiles/relay.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/relay.dir/cmake_clean.cmake
.PHONY : CMakeFiles/relay.dir/clean

CMakeFiles/relay.dir/depend:
	cd /home/johnsun/tcprelay/build/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/johnsun/tcprelay /home/johnsun/tcprelay /home/johnsun/tcprelay/build/debug /home/johnsun/tcprelay/build/debug /home/johnsun/tcprelay/build/debug/CMakeFiles/relay.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/relay.dir/depend

