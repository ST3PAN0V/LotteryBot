# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/stepanov/Documents/vs_code/github/lotteryBot

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/stepanov/Documents/vs_code/github/lotteryBot/build

# Include any dependencies generated for this target.
include CMakeFiles/LotteryBotActivate.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/LotteryBotActivate.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/LotteryBotActivate.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LotteryBotActivate.dir/flags.make

CMakeFiles/LotteryBotActivate.dir/sources/dataBaseTools/dataBase.cpp.o: CMakeFiles/LotteryBotActivate.dir/flags.make
CMakeFiles/LotteryBotActivate.dir/sources/dataBaseTools/dataBase.cpp.o: ../sources/dataBaseTools/dataBase.cpp
CMakeFiles/LotteryBotActivate.dir/sources/dataBaseTools/dataBase.cpp.o: CMakeFiles/LotteryBotActivate.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stepanov/Documents/vs_code/github/lotteryBot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LotteryBotActivate.dir/sources/dataBaseTools/dataBase.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/LotteryBotActivate.dir/sources/dataBaseTools/dataBase.cpp.o -MF CMakeFiles/LotteryBotActivate.dir/sources/dataBaseTools/dataBase.cpp.o.d -o CMakeFiles/LotteryBotActivate.dir/sources/dataBaseTools/dataBase.cpp.o -c /home/stepanov/Documents/vs_code/github/lotteryBot/sources/dataBaseTools/dataBase.cpp

CMakeFiles/LotteryBotActivate.dir/sources/dataBaseTools/dataBase.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LotteryBotActivate.dir/sources/dataBaseTools/dataBase.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stepanov/Documents/vs_code/github/lotteryBot/sources/dataBaseTools/dataBase.cpp > CMakeFiles/LotteryBotActivate.dir/sources/dataBaseTools/dataBase.cpp.i

CMakeFiles/LotteryBotActivate.dir/sources/dataBaseTools/dataBase.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LotteryBotActivate.dir/sources/dataBaseTools/dataBase.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stepanov/Documents/vs_code/github/lotteryBot/sources/dataBaseTools/dataBase.cpp -o CMakeFiles/LotteryBotActivate.dir/sources/dataBaseTools/dataBase.cpp.s

CMakeFiles/LotteryBotActivate.dir/sources/lotteryLogic/lottery.cpp.o: CMakeFiles/LotteryBotActivate.dir/flags.make
CMakeFiles/LotteryBotActivate.dir/sources/lotteryLogic/lottery.cpp.o: ../sources/lotteryLogic/lottery.cpp
CMakeFiles/LotteryBotActivate.dir/sources/lotteryLogic/lottery.cpp.o: CMakeFiles/LotteryBotActivate.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stepanov/Documents/vs_code/github/lotteryBot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/LotteryBotActivate.dir/sources/lotteryLogic/lottery.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/LotteryBotActivate.dir/sources/lotteryLogic/lottery.cpp.o -MF CMakeFiles/LotteryBotActivate.dir/sources/lotteryLogic/lottery.cpp.o.d -o CMakeFiles/LotteryBotActivate.dir/sources/lotteryLogic/lottery.cpp.o -c /home/stepanov/Documents/vs_code/github/lotteryBot/sources/lotteryLogic/lottery.cpp

CMakeFiles/LotteryBotActivate.dir/sources/lotteryLogic/lottery.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LotteryBotActivate.dir/sources/lotteryLogic/lottery.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stepanov/Documents/vs_code/github/lotteryBot/sources/lotteryLogic/lottery.cpp > CMakeFiles/LotteryBotActivate.dir/sources/lotteryLogic/lottery.cpp.i

CMakeFiles/LotteryBotActivate.dir/sources/lotteryLogic/lottery.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LotteryBotActivate.dir/sources/lotteryLogic/lottery.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stepanov/Documents/vs_code/github/lotteryBot/sources/lotteryLogic/lottery.cpp -o CMakeFiles/LotteryBotActivate.dir/sources/lotteryLogic/lottery.cpp.s

CMakeFiles/LotteryBotActivate.dir/sources/telegramBotLogic/telegramBot.cpp.o: CMakeFiles/LotteryBotActivate.dir/flags.make
CMakeFiles/LotteryBotActivate.dir/sources/telegramBotLogic/telegramBot.cpp.o: ../sources/telegramBotLogic/telegramBot.cpp
CMakeFiles/LotteryBotActivate.dir/sources/telegramBotLogic/telegramBot.cpp.o: CMakeFiles/LotteryBotActivate.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stepanov/Documents/vs_code/github/lotteryBot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/LotteryBotActivate.dir/sources/telegramBotLogic/telegramBot.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/LotteryBotActivate.dir/sources/telegramBotLogic/telegramBot.cpp.o -MF CMakeFiles/LotteryBotActivate.dir/sources/telegramBotLogic/telegramBot.cpp.o.d -o CMakeFiles/LotteryBotActivate.dir/sources/telegramBotLogic/telegramBot.cpp.o -c /home/stepanov/Documents/vs_code/github/lotteryBot/sources/telegramBotLogic/telegramBot.cpp

CMakeFiles/LotteryBotActivate.dir/sources/telegramBotLogic/telegramBot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LotteryBotActivate.dir/sources/telegramBotLogic/telegramBot.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stepanov/Documents/vs_code/github/lotteryBot/sources/telegramBotLogic/telegramBot.cpp > CMakeFiles/LotteryBotActivate.dir/sources/telegramBotLogic/telegramBot.cpp.i

CMakeFiles/LotteryBotActivate.dir/sources/telegramBotLogic/telegramBot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LotteryBotActivate.dir/sources/telegramBotLogic/telegramBot.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stepanov/Documents/vs_code/github/lotteryBot/sources/telegramBotLogic/telegramBot.cpp -o CMakeFiles/LotteryBotActivate.dir/sources/telegramBotLogic/telegramBot.cpp.s

CMakeFiles/LotteryBotActivate.dir/sources/main.cpp.o: CMakeFiles/LotteryBotActivate.dir/flags.make
CMakeFiles/LotteryBotActivate.dir/sources/main.cpp.o: ../sources/main.cpp
CMakeFiles/LotteryBotActivate.dir/sources/main.cpp.o: CMakeFiles/LotteryBotActivate.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stepanov/Documents/vs_code/github/lotteryBot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/LotteryBotActivate.dir/sources/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/LotteryBotActivate.dir/sources/main.cpp.o -MF CMakeFiles/LotteryBotActivate.dir/sources/main.cpp.o.d -o CMakeFiles/LotteryBotActivate.dir/sources/main.cpp.o -c /home/stepanov/Documents/vs_code/github/lotteryBot/sources/main.cpp

CMakeFiles/LotteryBotActivate.dir/sources/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LotteryBotActivate.dir/sources/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stepanov/Documents/vs_code/github/lotteryBot/sources/main.cpp > CMakeFiles/LotteryBotActivate.dir/sources/main.cpp.i

CMakeFiles/LotteryBotActivate.dir/sources/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LotteryBotActivate.dir/sources/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stepanov/Documents/vs_code/github/lotteryBot/sources/main.cpp -o CMakeFiles/LotteryBotActivate.dir/sources/main.cpp.s

# Object files for target LotteryBotActivate
LotteryBotActivate_OBJECTS = \
"CMakeFiles/LotteryBotActivate.dir/sources/dataBaseTools/dataBase.cpp.o" \
"CMakeFiles/LotteryBotActivate.dir/sources/lotteryLogic/lottery.cpp.o" \
"CMakeFiles/LotteryBotActivate.dir/sources/telegramBotLogic/telegramBot.cpp.o" \
"CMakeFiles/LotteryBotActivate.dir/sources/main.cpp.o"

# External object files for target LotteryBotActivate
LotteryBotActivate_EXTERNAL_OBJECTS =

LotteryBotActivate: CMakeFiles/LotteryBotActivate.dir/sources/dataBaseTools/dataBase.cpp.o
LotteryBotActivate: CMakeFiles/LotteryBotActivate.dir/sources/lotteryLogic/lottery.cpp.o
LotteryBotActivate: CMakeFiles/LotteryBotActivate.dir/sources/telegramBotLogic/telegramBot.cpp.o
LotteryBotActivate: CMakeFiles/LotteryBotActivate.dir/sources/main.cpp.o
LotteryBotActivate: CMakeFiles/LotteryBotActivate.dir/build.make
LotteryBotActivate: /usr/lib/x86_64-linux-gnu/libfmt.so.8.1.1
LotteryBotActivate: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.74.0
LotteryBotActivate: /usr/lib/x86_64-linux-gnu/libssl.so
LotteryBotActivate: /usr/lib/x86_64-linux-gnu/libcrypto.so
LotteryBotActivate: /usr/lib/x86_64-linux-gnu/libsqlite3.so
LotteryBotActivate: CMakeFiles/LotteryBotActivate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/stepanov/Documents/vs_code/github/lotteryBot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable LotteryBotActivate"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LotteryBotActivate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LotteryBotActivate.dir/build: LotteryBotActivate
.PHONY : CMakeFiles/LotteryBotActivate.dir/build

CMakeFiles/LotteryBotActivate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LotteryBotActivate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LotteryBotActivate.dir/clean

CMakeFiles/LotteryBotActivate.dir/depend:
	cd /home/stepanov/Documents/vs_code/github/lotteryBot/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/stepanov/Documents/vs_code/github/lotteryBot /home/stepanov/Documents/vs_code/github/lotteryBot /home/stepanov/Documents/vs_code/github/lotteryBot/build /home/stepanov/Documents/vs_code/github/lotteryBot/build /home/stepanov/Documents/vs_code/github/lotteryBot/build/CMakeFiles/LotteryBotActivate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LotteryBotActivate.dir/depend

