# CMAKE generated file: DO NOT EDIT!
# Generated by "MSYS Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = "/C/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "/C/Program Files/CMake/bin/cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /C/ti-software/R2D2/Build-environment/modules/BLUETOOTH

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /C/ti-software/R2D2/Build-environment/modules/BLUETOOTH/build

# Utility rule file for flash.

# Include the progress variables for this target.
include CMakeFiles/flash.dir/progress.make

CMakeFiles/flash:
	/C/ti-software/bossac-1.7.0/bossac.exe -pCOM3 -Ufalse -e -w -v -b arduino-template.bin -R

flash: CMakeFiles/flash
flash: CMakeFiles/flash.dir/build.make

.PHONY : flash

# Rule to build all files generated by this target.
CMakeFiles/flash.dir/build: flash

.PHONY : CMakeFiles/flash.dir/build

CMakeFiles/flash.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/flash.dir/cmake_clean.cmake
.PHONY : CMakeFiles/flash.dir/clean

CMakeFiles/flash.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MSYS Makefiles" /C/ti-software/R2D2/Build-environment/modules/BLUETOOTH /C/ti-software/R2D2/Build-environment/modules/BLUETOOTH /C/ti-software/R2D2/Build-environment/modules/BLUETOOTH/build /C/ti-software/R2D2/Build-environment/modules/BLUETOOTH/build /C/ti-software/R2D2/Build-environment/modules/BLUETOOTH/build/CMakeFiles/flash.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/flash.dir/depend

