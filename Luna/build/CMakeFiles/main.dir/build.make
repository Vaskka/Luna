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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.15.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.15.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/vaskka/Desktop/libluna/Luna

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/vaskka/Desktop/libluna/Luna/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/main.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vaskka/Desktop/libluna/Luna/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/main.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/main.c.o   -c /Users/vaskka/Desktop/libluna/Luna/main.c

CMakeFiles/main.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/vaskka/Desktop/libluna/Luna/main.c > CMakeFiles/main.dir/main.c.i

CMakeFiles/main.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/vaskka/Desktop/libluna/Luna/main.c -o CMakeFiles/main.dir/main.c.s

CMakeFiles/main.dir/linkedlist/linkedlist.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/linkedlist/linkedlist.c.o: ../linkedlist/linkedlist.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vaskka/Desktop/libluna/Luna/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/main.dir/linkedlist/linkedlist.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/linkedlist/linkedlist.c.o   -c /Users/vaskka/Desktop/libluna/Luna/linkedlist/linkedlist.c

CMakeFiles/main.dir/linkedlist/linkedlist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/linkedlist/linkedlist.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/vaskka/Desktop/libluna/Luna/linkedlist/linkedlist.c > CMakeFiles/main.dir/linkedlist/linkedlist.c.i

CMakeFiles/main.dir/linkedlist/linkedlist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/linkedlist/linkedlist.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/vaskka/Desktop/libluna/Luna/linkedlist/linkedlist.c -o CMakeFiles/main.dir/linkedlist/linkedlist.c.s

CMakeFiles/main.dir/arraylist/arraylist.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/arraylist/arraylist.c.o: ../arraylist/arraylist.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vaskka/Desktop/libluna/Luna/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/main.dir/arraylist/arraylist.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/arraylist/arraylist.c.o   -c /Users/vaskka/Desktop/libluna/Luna/arraylist/arraylist.c

CMakeFiles/main.dir/arraylist/arraylist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/arraylist/arraylist.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/vaskka/Desktop/libluna/Luna/arraylist/arraylist.c > CMakeFiles/main.dir/arraylist/arraylist.c.i

CMakeFiles/main.dir/arraylist/arraylist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/arraylist/arraylist.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/vaskka/Desktop/libluna/Luna/arraylist/arraylist.c -o CMakeFiles/main.dir/arraylist/arraylist.c.s

CMakeFiles/main.dir/common/struct_common.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/common/struct_common.c.o: ../common/struct_common.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vaskka/Desktop/libluna/Luna/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/main.dir/common/struct_common.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/common/struct_common.c.o   -c /Users/vaskka/Desktop/libluna/Luna/common/struct_common.c

CMakeFiles/main.dir/common/struct_common.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/common/struct_common.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/vaskka/Desktop/libluna/Luna/common/struct_common.c > CMakeFiles/main.dir/common/struct_common.c.i

CMakeFiles/main.dir/common/struct_common.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/common/struct_common.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/vaskka/Desktop/libluna/Luna/common/struct_common.c -o CMakeFiles/main.dir/common/struct_common.c.s

CMakeFiles/main.dir/datastruct/strtype_tree.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/datastruct/strtype_tree.c.o: ../datastruct/strtype_tree.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vaskka/Desktop/libluna/Luna/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/main.dir/datastruct/strtype_tree.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/datastruct/strtype_tree.c.o   -c /Users/vaskka/Desktop/libluna/Luna/datastruct/strtype_tree.c

CMakeFiles/main.dir/datastruct/strtype_tree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/datastruct/strtype_tree.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/vaskka/Desktop/libluna/Luna/datastruct/strtype_tree.c > CMakeFiles/main.dir/datastruct/strtype_tree.c.i

CMakeFiles/main.dir/datastruct/strtype_tree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/datastruct/strtype_tree.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/vaskka/Desktop/libluna/Luna/datastruct/strtype_tree.c -o CMakeFiles/main.dir/datastruct/strtype_tree.c.s

CMakeFiles/main.dir/datastruct/stringbuilder/stringbuilder.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/datastruct/stringbuilder/stringbuilder.c.o: ../datastruct/stringbuilder/stringbuilder.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vaskka/Desktop/libluna/Luna/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/main.dir/datastruct/stringbuilder/stringbuilder.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/datastruct/stringbuilder/stringbuilder.c.o   -c /Users/vaskka/Desktop/libluna/Luna/datastruct/stringbuilder/stringbuilder.c

CMakeFiles/main.dir/datastruct/stringbuilder/stringbuilder.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/datastruct/stringbuilder/stringbuilder.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/vaskka/Desktop/libluna/Luna/datastruct/stringbuilder/stringbuilder.c > CMakeFiles/main.dir/datastruct/stringbuilder/stringbuilder.c.i

CMakeFiles/main.dir/datastruct/stringbuilder/stringbuilder.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/datastruct/stringbuilder/stringbuilder.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/vaskka/Desktop/libluna/Luna/datastruct/stringbuilder/stringbuilder.c -o CMakeFiles/main.dir/datastruct/stringbuilder/stringbuilder.c.s

CMakeFiles/main.dir/file/file_util.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/file/file_util.c.o: ../file/file_util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vaskka/Desktop/libluna/Luna/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/main.dir/file/file_util.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/file/file_util.c.o   -c /Users/vaskka/Desktop/libluna/Luna/file/file_util.c

CMakeFiles/main.dir/file/file_util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/file/file_util.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/vaskka/Desktop/libluna/Luna/file/file_util.c > CMakeFiles/main.dir/file/file_util.c.i

CMakeFiles/main.dir/file/file_util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/file/file_util.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/vaskka/Desktop/libluna/Luna/file/file_util.c -o CMakeFiles/main.dir/file/file_util.c.s

CMakeFiles/main.dir/net/net_server_util.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/net/net_server_util.c.o: ../net/net_server_util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vaskka/Desktop/libluna/Luna/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/main.dir/net/net_server_util.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/net/net_server_util.c.o   -c /Users/vaskka/Desktop/libluna/Luna/net/net_server_util.c

CMakeFiles/main.dir/net/net_server_util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/net/net_server_util.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/vaskka/Desktop/libluna/Luna/net/net_server_util.c > CMakeFiles/main.dir/net/net_server_util.c.i

CMakeFiles/main.dir/net/net_server_util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/net/net_server_util.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/vaskka/Desktop/libluna/Luna/net/net_server_util.c -o CMakeFiles/main.dir/net/net_server_util.c.s

CMakeFiles/main.dir/utils/json/cJSON.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/utils/json/cJSON.c.o: ../utils/json/cJSON.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vaskka/Desktop/libluna/Luna/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/main.dir/utils/json/cJSON.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/utils/json/cJSON.c.o   -c /Users/vaskka/Desktop/libluna/Luna/utils/json/cJSON.c

CMakeFiles/main.dir/utils/json/cJSON.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/utils/json/cJSON.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/vaskka/Desktop/libluna/Luna/utils/json/cJSON.c > CMakeFiles/main.dir/utils/json/cJSON.c.i

CMakeFiles/main.dir/utils/json/cJSON.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/utils/json/cJSON.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/vaskka/Desktop/libluna/Luna/utils/json/cJSON.c -o CMakeFiles/main.dir/utils/json/cJSON.c.s

CMakeFiles/main.dir/utils/util.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/utils/util.c.o: ../utils/util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vaskka/Desktop/libluna/Luna/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/main.dir/utils/util.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/utils/util.c.o   -c /Users/vaskka/Desktop/libluna/Luna/utils/util.c

CMakeFiles/main.dir/utils/util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/utils/util.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/vaskka/Desktop/libluna/Luna/utils/util.c > CMakeFiles/main.dir/utils/util.c.i

CMakeFiles/main.dir/utils/util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/utils/util.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/vaskka/Desktop/libluna/Luna/utils/util.c -o CMakeFiles/main.dir/utils/util.c.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.c.o" \
"CMakeFiles/main.dir/linkedlist/linkedlist.c.o" \
"CMakeFiles/main.dir/arraylist/arraylist.c.o" \
"CMakeFiles/main.dir/common/struct_common.c.o" \
"CMakeFiles/main.dir/datastruct/strtype_tree.c.o" \
"CMakeFiles/main.dir/datastruct/stringbuilder/stringbuilder.c.o" \
"CMakeFiles/main.dir/file/file_util.c.o" \
"CMakeFiles/main.dir/net/net_server_util.c.o" \
"CMakeFiles/main.dir/utils/json/cJSON.c.o" \
"CMakeFiles/main.dir/utils/util.c.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/main.c.o
main: CMakeFiles/main.dir/linkedlist/linkedlist.c.o
main: CMakeFiles/main.dir/arraylist/arraylist.c.o
main: CMakeFiles/main.dir/common/struct_common.c.o
main: CMakeFiles/main.dir/datastruct/strtype_tree.c.o
main: CMakeFiles/main.dir/datastruct/stringbuilder/stringbuilder.c.o
main: CMakeFiles/main.dir/file/file_util.c.o
main: CMakeFiles/main.dir/net/net_server_util.c.o
main: CMakeFiles/main.dir/utils/json/cJSON.c.o
main: CMakeFiles/main.dir/utils/util.c.o
main: CMakeFiles/main.dir/build.make
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/vaskka/Desktop/libluna/Luna/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking C executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main

.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /Users/vaskka/Desktop/libluna/Luna/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/vaskka/Desktop/libluna/Luna /Users/vaskka/Desktop/libluna/Luna /Users/vaskka/Desktop/libluna/Luna/build /Users/vaskka/Desktop/libluna/Luna/build /Users/vaskka/Desktop/libluna/Luna/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

