# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/philip/Documents/apps/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/philip/Documents/apps/clion/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/philip/Documents/projects/hivemind

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/philip/Documents/projects/hivemind/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/hivemind.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hivemind.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hivemind.dir/flags.make

CMakeFiles/hivemind.dir/main.cpp.o: CMakeFiles/hivemind.dir/flags.make
CMakeFiles/hivemind.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/philip/Documents/projects/hivemind/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hivemind.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hivemind.dir/main.cpp.o -c /home/philip/Documents/projects/hivemind/main.cpp

CMakeFiles/hivemind.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hivemind.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/philip/Documents/projects/hivemind/main.cpp > CMakeFiles/hivemind.dir/main.cpp.i

CMakeFiles/hivemind.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hivemind.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/philip/Documents/projects/hivemind/main.cpp -o CMakeFiles/hivemind.dir/main.cpp.s

CMakeFiles/hivemind.dir/Robot.cpp.o: CMakeFiles/hivemind.dir/flags.make
CMakeFiles/hivemind.dir/Robot.cpp.o: ../Robot.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/philip/Documents/projects/hivemind/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/hivemind.dir/Robot.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hivemind.dir/Robot.cpp.o -c /home/philip/Documents/projects/hivemind/Robot.cpp

CMakeFiles/hivemind.dir/Robot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hivemind.dir/Robot.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/philip/Documents/projects/hivemind/Robot.cpp > CMakeFiles/hivemind.dir/Robot.cpp.i

CMakeFiles/hivemind.dir/Robot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hivemind.dir/Robot.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/philip/Documents/projects/hivemind/Robot.cpp -o CMakeFiles/hivemind.dir/Robot.cpp.s

CMakeFiles/hivemind.dir/GridMap.cpp.o: CMakeFiles/hivemind.dir/flags.make
CMakeFiles/hivemind.dir/GridMap.cpp.o: ../GridMap.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/philip/Documents/projects/hivemind/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/hivemind.dir/GridMap.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hivemind.dir/GridMap.cpp.o -c /home/philip/Documents/projects/hivemind/GridMap.cpp

CMakeFiles/hivemind.dir/GridMap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hivemind.dir/GridMap.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/philip/Documents/projects/hivemind/GridMap.cpp > CMakeFiles/hivemind.dir/GridMap.cpp.i

CMakeFiles/hivemind.dir/GridMap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hivemind.dir/GridMap.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/philip/Documents/projects/hivemind/GridMap.cpp -o CMakeFiles/hivemind.dir/GridMap.cpp.s

CMakeFiles/hivemind.dir/Pather.cpp.o: CMakeFiles/hivemind.dir/flags.make
CMakeFiles/hivemind.dir/Pather.cpp.o: ../Pather.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/philip/Documents/projects/hivemind/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/hivemind.dir/Pather.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hivemind.dir/Pather.cpp.o -c /home/philip/Documents/projects/hivemind/Pather.cpp

CMakeFiles/hivemind.dir/Pather.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hivemind.dir/Pather.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/philip/Documents/projects/hivemind/Pather.cpp > CMakeFiles/hivemind.dir/Pather.cpp.i

CMakeFiles/hivemind.dir/Pather.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hivemind.dir/Pather.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/philip/Documents/projects/hivemind/Pather.cpp -o CMakeFiles/hivemind.dir/Pather.cpp.s

# Object files for target hivemind
hivemind_OBJECTS = \
"CMakeFiles/hivemind.dir/main.cpp.o" \
"CMakeFiles/hivemind.dir/Robot.cpp.o" \
"CMakeFiles/hivemind.dir/GridMap.cpp.o" \
"CMakeFiles/hivemind.dir/Pather.cpp.o"

# External object files for target hivemind
hivemind_EXTERNAL_OBJECTS =

hivemind: CMakeFiles/hivemind.dir/main.cpp.o
hivemind: CMakeFiles/hivemind.dir/Robot.cpp.o
hivemind: CMakeFiles/hivemind.dir/GridMap.cpp.o
hivemind: CMakeFiles/hivemind.dir/Pather.cpp.o
hivemind: CMakeFiles/hivemind.dir/build.make
hivemind: /usr/lib/x86_64-linux-gnu/libOpenGL.so
hivemind: /usr/lib/x86_64-linux-gnu/libGLX.so
hivemind: /usr/lib/x86_64-linux-gnu/libGLU.so
hivemind: external/glfw-3.1.2/src/libglfw3.a
hivemind: external/libGLEW_1130.a
hivemind: /usr/lib/x86_64-linux-gnu/libOpenGL.so
hivemind: /usr/lib/x86_64-linux-gnu/libGLX.so
hivemind: /usr/lib/x86_64-linux-gnu/libGLU.so
hivemind: /usr/lib/x86_64-linux-gnu/librt.so
hivemind: /usr/lib/x86_64-linux-gnu/libm.so
hivemind: /usr/lib/x86_64-linux-gnu/libX11.so
hivemind: /usr/lib/x86_64-linux-gnu/libXrandr.so
hivemind: /usr/lib/x86_64-linux-gnu/libXinerama.so
hivemind: /usr/lib/x86_64-linux-gnu/libXi.so
hivemind: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
hivemind: /usr/lib/x86_64-linux-gnu/libXcursor.so
hivemind: /usr/lib/x86_64-linux-gnu/librt.so
hivemind: /usr/lib/x86_64-linux-gnu/libm.so
hivemind: /usr/lib/x86_64-linux-gnu/libX11.so
hivemind: /usr/lib/x86_64-linux-gnu/libXrandr.so
hivemind: /usr/lib/x86_64-linux-gnu/libXinerama.so
hivemind: /usr/lib/x86_64-linux-gnu/libXi.so
hivemind: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
hivemind: /usr/lib/x86_64-linux-gnu/libXcursor.so
hivemind: CMakeFiles/hivemind.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/philip/Documents/projects/hivemind/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable hivemind"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hivemind.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hivemind.dir/build: hivemind

.PHONY : CMakeFiles/hivemind.dir/build

CMakeFiles/hivemind.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hivemind.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hivemind.dir/clean

CMakeFiles/hivemind.dir/depend:
	cd /home/philip/Documents/projects/hivemind/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/philip/Documents/projects/hivemind /home/philip/Documents/projects/hivemind /home/philip/Documents/projects/hivemind/cmake-build-debug /home/philip/Documents/projects/hivemind/cmake-build-debug /home/philip/Documents/projects/hivemind/cmake-build-debug/CMakeFiles/hivemind.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hivemind.dir/depend

