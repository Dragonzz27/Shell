# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /usr/local/cmake/cmake-3.27.4-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /usr/local/cmake/cmake-3.27.4-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dragonzz/Shell

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dragonzz/Shell/build

# Include any dependencies generated for this target.
include CMakeFiles/shell.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/shell.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/shell.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/shell.dir/flags.make

CMakeFiles/shell.dir/src/builtin.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/builtin.c.o: /home/dragonzz/Shell/src/builtin.c
CMakeFiles/shell.dir/src/builtin.c.o: CMakeFiles/shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dragonzz/Shell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/shell.dir/src/builtin.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/shell.dir/src/builtin.c.o -MF CMakeFiles/shell.dir/src/builtin.c.o.d -o CMakeFiles/shell.dir/src/builtin.c.o -c /home/dragonzz/Shell/src/builtin.c

CMakeFiles/shell.dir/src/builtin.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/shell.dir/src/builtin.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dragonzz/Shell/src/builtin.c > CMakeFiles/shell.dir/src/builtin.c.i

CMakeFiles/shell.dir/src/builtin.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/shell.dir/src/builtin.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dragonzz/Shell/src/builtin.c -o CMakeFiles/shell.dir/src/builtin.c.s

CMakeFiles/shell.dir/src/command.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/command.c.o: /home/dragonzz/Shell/src/command.c
CMakeFiles/shell.dir/src/command.c.o: CMakeFiles/shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dragonzz/Shell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/shell.dir/src/command.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/shell.dir/src/command.c.o -MF CMakeFiles/shell.dir/src/command.c.o.d -o CMakeFiles/shell.dir/src/command.c.o -c /home/dragonzz/Shell/src/command.c

CMakeFiles/shell.dir/src/command.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/shell.dir/src/command.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dragonzz/Shell/src/command.c > CMakeFiles/shell.dir/src/command.c.i

CMakeFiles/shell.dir/src/command.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/shell.dir/src/command.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dragonzz/Shell/src/command.c -o CMakeFiles/shell.dir/src/command.c.s

CMakeFiles/shell.dir/src/main.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/main.c.o: /home/dragonzz/Shell/src/main.c
CMakeFiles/shell.dir/src/main.c.o: CMakeFiles/shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dragonzz/Shell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/shell.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/shell.dir/src/main.c.o -MF CMakeFiles/shell.dir/src/main.c.o.d -o CMakeFiles/shell.dir/src/main.c.o -c /home/dragonzz/Shell/src/main.c

CMakeFiles/shell.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/shell.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dragonzz/Shell/src/main.c > CMakeFiles/shell.dir/src/main.c.i

CMakeFiles/shell.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/shell.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dragonzz/Shell/src/main.c -o CMakeFiles/shell.dir/src/main.c.s

CMakeFiles/shell.dir/src/process.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/process.c.o: /home/dragonzz/Shell/src/process.c
CMakeFiles/shell.dir/src/process.c.o: CMakeFiles/shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dragonzz/Shell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/shell.dir/src/process.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/shell.dir/src/process.c.o -MF CMakeFiles/shell.dir/src/process.c.o.d -o CMakeFiles/shell.dir/src/process.c.o -c /home/dragonzz/Shell/src/process.c

CMakeFiles/shell.dir/src/process.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/shell.dir/src/process.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dragonzz/Shell/src/process.c > CMakeFiles/shell.dir/src/process.c.i

CMakeFiles/shell.dir/src/process.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/shell.dir/src/process.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dragonzz/Shell/src/process.c -o CMakeFiles/shell.dir/src/process.c.s

CMakeFiles/shell.dir/src/utils.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/utils.c.o: /home/dragonzz/Shell/src/utils.c
CMakeFiles/shell.dir/src/utils.c.o: CMakeFiles/shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dragonzz/Shell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/shell.dir/src/utils.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/shell.dir/src/utils.c.o -MF CMakeFiles/shell.dir/src/utils.c.o.d -o CMakeFiles/shell.dir/src/utils.c.o -c /home/dragonzz/Shell/src/utils.c

CMakeFiles/shell.dir/src/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/shell.dir/src/utils.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dragonzz/Shell/src/utils.c > CMakeFiles/shell.dir/src/utils.c.i

CMakeFiles/shell.dir/src/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/shell.dir/src/utils.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dragonzz/Shell/src/utils.c -o CMakeFiles/shell.dir/src/utils.c.s

# Object files for target shell
shell_OBJECTS = \
"CMakeFiles/shell.dir/src/builtin.c.o" \
"CMakeFiles/shell.dir/src/command.c.o" \
"CMakeFiles/shell.dir/src/main.c.o" \
"CMakeFiles/shell.dir/src/process.c.o" \
"CMakeFiles/shell.dir/src/utils.c.o"

# External object files for target shell
shell_EXTERNAL_OBJECTS =

/home/dragonzz/Shell/bin/shell: CMakeFiles/shell.dir/src/builtin.c.o
/home/dragonzz/Shell/bin/shell: CMakeFiles/shell.dir/src/command.c.o
/home/dragonzz/Shell/bin/shell: CMakeFiles/shell.dir/src/main.c.o
/home/dragonzz/Shell/bin/shell: CMakeFiles/shell.dir/src/process.c.o
/home/dragonzz/Shell/bin/shell: CMakeFiles/shell.dir/src/utils.c.o
/home/dragonzz/Shell/bin/shell: CMakeFiles/shell.dir/build.make
/home/dragonzz/Shell/bin/shell: CMakeFiles/shell.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/dragonzz/Shell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable /home/dragonzz/Shell/bin/shell"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shell.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/shell.dir/build: /home/dragonzz/Shell/bin/shell
.PHONY : CMakeFiles/shell.dir/build

CMakeFiles/shell.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/shell.dir/cmake_clean.cmake
.PHONY : CMakeFiles/shell.dir/clean

CMakeFiles/shell.dir/depend:
	cd /home/dragonzz/Shell/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dragonzz/Shell /home/dragonzz/Shell /home/dragonzz/Shell/build /home/dragonzz/Shell/build /home/dragonzz/Shell/build/CMakeFiles/shell.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/shell.dir/depend

