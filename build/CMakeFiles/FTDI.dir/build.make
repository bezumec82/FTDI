# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\PROJECTS\FTDI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\PROJECTS\FTDI\build

# Include any dependencies generated for this target.
include CMakeFiles/FTDI.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/FTDI.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FTDI.dir/flags.make

CMakeFiles/FTDI.dir/src/main.cpp.obj: CMakeFiles/FTDI.dir/flags.make
CMakeFiles/FTDI.dir/src/main.cpp.obj: CMakeFiles/FTDI.dir/includes_CXX.rsp
CMakeFiles/FTDI.dir/src/main.cpp.obj: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\PROJECTS\FTDI\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FTDI.dir/src/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\FTDI.dir\src\main.cpp.obj -c D:\PROJECTS\FTDI\src\main.cpp

CMakeFiles/FTDI.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FTDI.dir/src/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\PROJECTS\FTDI\src\main.cpp > CMakeFiles\FTDI.dir\src\main.cpp.i

CMakeFiles/FTDI.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FTDI.dir/src/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\PROJECTS\FTDI\src\main.cpp -o CMakeFiles\FTDI.dir\src\main.cpp.s

# Object files for target FTDI
FTDI_OBJECTS = \
"CMakeFiles/FTDI.dir/src/main.cpp.obj"

# External object files for target FTDI
FTDI_EXTERNAL_OBJECTS =

../out/FTDI.exe: CMakeFiles/FTDI.dir/src/main.cpp.obj
../out/FTDI.exe: CMakeFiles/FTDI.dir/build.make
../out/FTDI.exe: CMakeFiles/FTDI.dir/linklibs.rsp
../out/FTDI.exe: CMakeFiles/FTDI.dir/objects1.rsp
../out/FTDI.exe: CMakeFiles/FTDI.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\PROJECTS\FTDI\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ..\out\FTDI.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\FTDI.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FTDI.dir/build: ../out/FTDI.exe

.PHONY : CMakeFiles/FTDI.dir/build

CMakeFiles/FTDI.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\FTDI.dir\cmake_clean.cmake
.PHONY : CMakeFiles/FTDI.dir/clean

CMakeFiles/FTDI.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\PROJECTS\FTDI D:\PROJECTS\FTDI D:\PROJECTS\FTDI\build D:\PROJECTS\FTDI\build D:\PROJECTS\FTDI\build\CMakeFiles\FTDI.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FTDI.dir/depend
