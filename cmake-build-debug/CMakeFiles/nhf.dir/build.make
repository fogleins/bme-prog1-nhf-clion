# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.2.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Simon\Google Drive\BME\prog1\nhf"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Simon\Google Drive\BME\prog1\nhf\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/nhf.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/nhf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/nhf.dir/flags.make

CMakeFiles/nhf.dir/main.c.obj: CMakeFiles/nhf.dir/flags.make
CMakeFiles/nhf.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Simon\Google Drive\BME\prog1\nhf\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/nhf.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\nhf.dir\main.c.obj   -c "C:\Users\Simon\Google Drive\BME\prog1\nhf\main.c"

CMakeFiles/nhf.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/nhf.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\Simon\Google Drive\BME\prog1\nhf\main.c" > CMakeFiles\nhf.dir\main.c.i

CMakeFiles/nhf.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/nhf.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\Simon\Google Drive\BME\prog1\nhf\main.c" -o CMakeFiles\nhf.dir\main.c.s

# Object files for target nhf
nhf_OBJECTS = \
"CMakeFiles/nhf.dir/main.c.obj"

# External object files for target nhf
nhf_EXTERNAL_OBJECTS =

nhf.exe: CMakeFiles/nhf.dir/main.c.obj
nhf.exe: CMakeFiles/nhf.dir/build.make
nhf.exe: CMakeFiles/nhf.dir/linklibs.rsp
nhf.exe: CMakeFiles/nhf.dir/objects1.rsp
nhf.exe: CMakeFiles/nhf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Simon\Google Drive\BME\prog1\nhf\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable nhf.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\nhf.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/nhf.dir/build: nhf.exe

.PHONY : CMakeFiles/nhf.dir/build

CMakeFiles/nhf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\nhf.dir\cmake_clean.cmake
.PHONY : CMakeFiles/nhf.dir/clean

CMakeFiles/nhf.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Simon\Google Drive\BME\prog1\nhf" "C:\Users\Simon\Google Drive\BME\prog1\nhf" "C:\Users\Simon\Google Drive\BME\prog1\nhf\cmake-build-debug" "C:\Users\Simon\Google Drive\BME\prog1\nhf\cmake-build-debug" "C:\Users\Simon\Google Drive\BME\prog1\nhf\cmake-build-debug\CMakeFiles\nhf.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/nhf.dir/depend

