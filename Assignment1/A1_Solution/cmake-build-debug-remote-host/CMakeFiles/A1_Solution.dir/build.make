# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/undergrad/0/enshen/workspace/assignment1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/undergrad/0/enshen/workspace/assignment1/cmake-build-debug-remote-host

# Include any dependencies generated for this target.
include CMakeFiles/A1_Solution.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/A1_Solution.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/A1_Solution.dir/flags.make

CMakeFiles/A1_Solution.dir/main.cpp.o: CMakeFiles/A1_Solution.dir/flags.make
CMakeFiles/A1_Solution.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/undergrad/0/enshen/workspace/assignment1/cmake-build-debug-remote-host/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/A1_Solution.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/A1_Solution.dir/main.cpp.o -c /home/undergrad/0/enshen/workspace/assignment1/main.cpp

CMakeFiles/A1_Solution.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A1_Solution.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/undergrad/0/enshen/workspace/assignment1/main.cpp > CMakeFiles/A1_Solution.dir/main.cpp.i

CMakeFiles/A1_Solution.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A1_Solution.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/undergrad/0/enshen/workspace/assignment1/main.cpp -o CMakeFiles/A1_Solution.dir/main.cpp.s

CMakeFiles/A1_Solution.dir/db_library/dbComponents.cpp.o: CMakeFiles/A1_Solution.dir/flags.make
CMakeFiles/A1_Solution.dir/db_library/dbComponents.cpp.o: ../db_library/dbComponents.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/undergrad/0/enshen/workspace/assignment1/cmake-build-debug-remote-host/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/A1_Solution.dir/db_library/dbComponents.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/A1_Solution.dir/db_library/dbComponents.cpp.o -c /home/undergrad/0/enshen/workspace/assignment1/db_library/dbComponents.cpp

CMakeFiles/A1_Solution.dir/db_library/dbComponents.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A1_Solution.dir/db_library/dbComponents.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/undergrad/0/enshen/workspace/assignment1/db_library/dbComponents.cpp > CMakeFiles/A1_Solution.dir/db_library/dbComponents.cpp.i

CMakeFiles/A1_Solution.dir/db_library/dbComponents.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A1_Solution.dir/db_library/dbComponents.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/undergrad/0/enshen/workspace/assignment1/db_library/dbComponents.cpp -o CMakeFiles/A1_Solution.dir/db_library/dbComponents.cpp.s

CMakeFiles/A1_Solution.dir/BplusTree_library/BplusTree.cpp.o: CMakeFiles/A1_Solution.dir/flags.make
CMakeFiles/A1_Solution.dir/BplusTree_library/BplusTree.cpp.o: ../BplusTree_library/BplusTree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/undergrad/0/enshen/workspace/assignment1/cmake-build-debug-remote-host/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/A1_Solution.dir/BplusTree_library/BplusTree.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/A1_Solution.dir/BplusTree_library/BplusTree.cpp.o -c /home/undergrad/0/enshen/workspace/assignment1/BplusTree_library/BplusTree.cpp

CMakeFiles/A1_Solution.dir/BplusTree_library/BplusTree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A1_Solution.dir/BplusTree_library/BplusTree.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/undergrad/0/enshen/workspace/assignment1/BplusTree_library/BplusTree.cpp > CMakeFiles/A1_Solution.dir/BplusTree_library/BplusTree.cpp.i

CMakeFiles/A1_Solution.dir/BplusTree_library/BplusTree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A1_Solution.dir/BplusTree_library/BplusTree.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/undergrad/0/enshen/workspace/assignment1/BplusTree_library/BplusTree.cpp -o CMakeFiles/A1_Solution.dir/BplusTree_library/BplusTree.cpp.s

# Object files for target A1_Solution
A1_Solution_OBJECTS = \
"CMakeFiles/A1_Solution.dir/main.cpp.o" \
"CMakeFiles/A1_Solution.dir/db_library/dbComponents.cpp.o" \
"CMakeFiles/A1_Solution.dir/BplusTree_library/BplusTree.cpp.o"

# External object files for target A1_Solution
A1_Solution_EXTERNAL_OBJECTS =

A1_Solution: CMakeFiles/A1_Solution.dir/main.cpp.o
A1_Solution: CMakeFiles/A1_Solution.dir/db_library/dbComponents.cpp.o
A1_Solution: CMakeFiles/A1_Solution.dir/BplusTree_library/BplusTree.cpp.o
A1_Solution: CMakeFiles/A1_Solution.dir/build.make
A1_Solution: CMakeFiles/A1_Solution.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/undergrad/0/enshen/workspace/assignment1/cmake-build-debug-remote-host/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable A1_Solution"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/A1_Solution.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/A1_Solution.dir/build: A1_Solution

.PHONY : CMakeFiles/A1_Solution.dir/build

CMakeFiles/A1_Solution.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/A1_Solution.dir/cmake_clean.cmake
.PHONY : CMakeFiles/A1_Solution.dir/clean

CMakeFiles/A1_Solution.dir/depend:
	cd /home/undergrad/0/enshen/workspace/assignment1/cmake-build-debug-remote-host && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/undergrad/0/enshen/workspace/assignment1 /home/undergrad/0/enshen/workspace/assignment1 /home/undergrad/0/enshen/workspace/assignment1/cmake-build-debug-remote-host /home/undergrad/0/enshen/workspace/assignment1/cmake-build-debug-remote-host /home/undergrad/0/enshen/workspace/assignment1/cmake-build-debug-remote-host/CMakeFiles/A1_Solution.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/A1_Solution.dir/depend

