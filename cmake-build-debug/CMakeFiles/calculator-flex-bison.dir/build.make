# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\Project\Compile\CompilerTools\msys64\mingw64\bin\cmake.exe

# The command to remove a file.
RM = D:\Project\Compile\CompilerTools\msys64\mingw64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Project\Compile\lab3\MiniC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Project\Compile\lab3\MiniC\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/calculator-flex-bison.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/calculator-flex-bison.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/calculator-flex-bison.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/calculator-flex-bison.dir/flags.make

D:/Project/Compile/lab3/MiniC/calculator_lex.cpp: D:/Project/Compile/lab3/MiniC/calculator.l
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=D:\Project\Compile\lab3\MiniC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating D:/Project/Compile/lab3/MiniC/calculator_lex.cpp, D:/Project/Compile/lab3/MiniC/calculator_lex.h"
	D:\Project\Compile\CompilerTools\msys64\usr\bin\flex.exe -o D:/Project/Compile/lab3/MiniC/calculator_lex.cpp --header-file=D:/Project/Compile/lab3/MiniC/calculator_lex.h D:/Project/Compile/lab3/MiniC/calculator.l

D:/Project/Compile/lab3/MiniC/calculator_lex.h: D:/Project/Compile/lab3/MiniC/calculator_lex.cpp
	@$(CMAKE_COMMAND) -E touch_nocreate D:\Project\Compile\lab3\MiniC\calculator_lex.h

D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp: D:/Project/Compile/lab3/MiniC/calculator.y
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=D:\Project\Compile\lab3\MiniC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp, D:/Project/Compile/lab3/MiniC/calculator_yacc.h"
	D:\Project\Compile\CompilerTools\msys64\usr\bin\bison.exe -d -o D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp --header=D:/Project/Compile/lab3/MiniC/calculator_yacc.h D:/Project/Compile/lab3/MiniC/calculator.y

D:/Project/Compile/lab3/MiniC/calculator_yacc.h: D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp
	@$(CMAKE_COMMAND) -E touch_nocreate D:\Project\Compile\lab3\MiniC\calculator_yacc.h

CMakeFiles/calculator-flex-bison.dir/calculator_lex.cpp.obj: CMakeFiles/calculator-flex-bison.dir/flags.make
CMakeFiles/calculator-flex-bison.dir/calculator_lex.cpp.obj: CMakeFiles/calculator-flex-bison.dir/includes_CXX.rsp
CMakeFiles/calculator-flex-bison.dir/calculator_lex.cpp.obj: D:/Project/Compile/lab3/MiniC/calculator_lex.cpp
CMakeFiles/calculator-flex-bison.dir/calculator_lex.cpp.obj: CMakeFiles/calculator-flex-bison.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Project\Compile\lab3\MiniC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/calculator-flex-bison.dir/calculator_lex.cpp.obj"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/calculator-flex-bison.dir/calculator_lex.cpp.obj -MF CMakeFiles\calculator-flex-bison.dir\calculator_lex.cpp.obj.d -o CMakeFiles\calculator-flex-bison.dir\calculator_lex.cpp.obj -c D:\Project\Compile\lab3\MiniC\calculator_lex.cpp

CMakeFiles/calculator-flex-bison.dir/calculator_lex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calculator-flex-bison.dir/calculator_lex.cpp.i"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\Compile\lab3\MiniC\calculator_lex.cpp > CMakeFiles\calculator-flex-bison.dir\calculator_lex.cpp.i

CMakeFiles/calculator-flex-bison.dir/calculator_lex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calculator-flex-bison.dir/calculator_lex.cpp.s"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\Compile\lab3\MiniC\calculator_lex.cpp -o CMakeFiles\calculator-flex-bison.dir\calculator_lex.cpp.s

CMakeFiles/calculator-flex-bison.dir/calculator_yacc.cpp.obj: CMakeFiles/calculator-flex-bison.dir/flags.make
CMakeFiles/calculator-flex-bison.dir/calculator_yacc.cpp.obj: CMakeFiles/calculator-flex-bison.dir/includes_CXX.rsp
CMakeFiles/calculator-flex-bison.dir/calculator_yacc.cpp.obj: D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp
CMakeFiles/calculator-flex-bison.dir/calculator_yacc.cpp.obj: CMakeFiles/calculator-flex-bison.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Project\Compile\lab3\MiniC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/calculator-flex-bison.dir/calculator_yacc.cpp.obj"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/calculator-flex-bison.dir/calculator_yacc.cpp.obj -MF CMakeFiles\calculator-flex-bison.dir\calculator_yacc.cpp.obj.d -o CMakeFiles\calculator-flex-bison.dir\calculator_yacc.cpp.obj -c D:\Project\Compile\lab3\MiniC\calculator_yacc.cpp

CMakeFiles/calculator-flex-bison.dir/calculator_yacc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calculator-flex-bison.dir/calculator_yacc.cpp.i"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\Compile\lab3\MiniC\calculator_yacc.cpp > CMakeFiles\calculator-flex-bison.dir\calculator_yacc.cpp.i

CMakeFiles/calculator-flex-bison.dir/calculator_yacc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calculator-flex-bison.dir/calculator_yacc.cpp.s"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\Compile\lab3\MiniC\calculator_yacc.cpp -o CMakeFiles\calculator-flex-bison.dir\calculator_yacc.cpp.s

CMakeFiles/calculator-flex-bison.dir/ast.cpp.obj: CMakeFiles/calculator-flex-bison.dir/flags.make
CMakeFiles/calculator-flex-bison.dir/ast.cpp.obj: CMakeFiles/calculator-flex-bison.dir/includes_CXX.rsp
CMakeFiles/calculator-flex-bison.dir/ast.cpp.obj: D:/Project/Compile/lab3/MiniC/ast.cpp
CMakeFiles/calculator-flex-bison.dir/ast.cpp.obj: CMakeFiles/calculator-flex-bison.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Project\Compile\lab3\MiniC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/calculator-flex-bison.dir/ast.cpp.obj"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/calculator-flex-bison.dir/ast.cpp.obj -MF CMakeFiles\calculator-flex-bison.dir\ast.cpp.obj.d -o CMakeFiles\calculator-flex-bison.dir\ast.cpp.obj -c D:\Project\Compile\lab3\MiniC\ast.cpp

CMakeFiles/calculator-flex-bison.dir/ast.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calculator-flex-bison.dir/ast.cpp.i"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\Compile\lab3\MiniC\ast.cpp > CMakeFiles\calculator-flex-bison.dir\ast.cpp.i

CMakeFiles/calculator-flex-bison.dir/ast.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calculator-flex-bison.dir/ast.cpp.s"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\Compile\lab3\MiniC\ast.cpp -o CMakeFiles\calculator-flex-bison.dir\ast.cpp.s

CMakeFiles/calculator-flex-bison.dir/expr.cpp.obj: CMakeFiles/calculator-flex-bison.dir/flags.make
CMakeFiles/calculator-flex-bison.dir/expr.cpp.obj: CMakeFiles/calculator-flex-bison.dir/includes_CXX.rsp
CMakeFiles/calculator-flex-bison.dir/expr.cpp.obj: D:/Project/Compile/lab3/MiniC/expr.cpp
CMakeFiles/calculator-flex-bison.dir/expr.cpp.obj: CMakeFiles/calculator-flex-bison.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Project\Compile\lab3\MiniC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/calculator-flex-bison.dir/expr.cpp.obj"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/calculator-flex-bison.dir/expr.cpp.obj -MF CMakeFiles\calculator-flex-bison.dir\expr.cpp.obj.d -o CMakeFiles\calculator-flex-bison.dir\expr.cpp.obj -c D:\Project\Compile\lab3\MiniC\expr.cpp

CMakeFiles/calculator-flex-bison.dir/expr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calculator-flex-bison.dir/expr.cpp.i"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\Compile\lab3\MiniC\expr.cpp > CMakeFiles\calculator-flex-bison.dir\expr.cpp.i

CMakeFiles/calculator-flex-bison.dir/expr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calculator-flex-bison.dir/expr.cpp.s"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\Compile\lab3\MiniC\expr.cpp -o CMakeFiles\calculator-flex-bison.dir\expr.cpp.s

CMakeFiles/calculator-flex-bison.dir/main.cpp.obj: CMakeFiles/calculator-flex-bison.dir/flags.make
CMakeFiles/calculator-flex-bison.dir/main.cpp.obj: CMakeFiles/calculator-flex-bison.dir/includes_CXX.rsp
CMakeFiles/calculator-flex-bison.dir/main.cpp.obj: D:/Project/Compile/lab3/MiniC/main.cpp
CMakeFiles/calculator-flex-bison.dir/main.cpp.obj: CMakeFiles/calculator-flex-bison.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Project\Compile\lab3\MiniC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/calculator-flex-bison.dir/main.cpp.obj"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/calculator-flex-bison.dir/main.cpp.obj -MF CMakeFiles\calculator-flex-bison.dir\main.cpp.obj.d -o CMakeFiles\calculator-flex-bison.dir\main.cpp.obj -c D:\Project\Compile\lab3\MiniC\main.cpp

CMakeFiles/calculator-flex-bison.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calculator-flex-bison.dir/main.cpp.i"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\Compile\lab3\MiniC\main.cpp > CMakeFiles\calculator-flex-bison.dir\main.cpp.i

CMakeFiles/calculator-flex-bison.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calculator-flex-bison.dir/main.cpp.s"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\Compile\lab3\MiniC\main.cpp -o CMakeFiles\calculator-flex-bison.dir\main.cpp.s

CMakeFiles/calculator-flex-bison.dir/graph.cpp.obj: CMakeFiles/calculator-flex-bison.dir/flags.make
CMakeFiles/calculator-flex-bison.dir/graph.cpp.obj: CMakeFiles/calculator-flex-bison.dir/includes_CXX.rsp
CMakeFiles/calculator-flex-bison.dir/graph.cpp.obj: D:/Project/Compile/lab3/MiniC/graph.cpp
CMakeFiles/calculator-flex-bison.dir/graph.cpp.obj: CMakeFiles/calculator-flex-bison.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Project\Compile\lab3\MiniC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/calculator-flex-bison.dir/graph.cpp.obj"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/calculator-flex-bison.dir/graph.cpp.obj -MF CMakeFiles\calculator-flex-bison.dir\graph.cpp.obj.d -o CMakeFiles\calculator-flex-bison.dir\graph.cpp.obj -c D:\Project\Compile\lab3\MiniC\graph.cpp

CMakeFiles/calculator-flex-bison.dir/graph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calculator-flex-bison.dir/graph.cpp.i"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\Compile\lab3\MiniC\graph.cpp > CMakeFiles\calculator-flex-bison.dir\graph.cpp.i

CMakeFiles/calculator-flex-bison.dir/graph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calculator-flex-bison.dir/graph.cpp.s"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\Compile\lab3\MiniC\graph.cpp -o CMakeFiles\calculator-flex-bison.dir\graph.cpp.s

CMakeFiles/calculator-flex-bison.dir/common.cpp.obj: CMakeFiles/calculator-flex-bison.dir/flags.make
CMakeFiles/calculator-flex-bison.dir/common.cpp.obj: CMakeFiles/calculator-flex-bison.dir/includes_CXX.rsp
CMakeFiles/calculator-flex-bison.dir/common.cpp.obj: D:/Project/Compile/lab3/MiniC/common.cpp
CMakeFiles/calculator-flex-bison.dir/common.cpp.obj: CMakeFiles/calculator-flex-bison.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Project\Compile\lab3\MiniC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/calculator-flex-bison.dir/common.cpp.obj"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/calculator-flex-bison.dir/common.cpp.obj -MF CMakeFiles\calculator-flex-bison.dir\common.cpp.obj.d -o CMakeFiles\calculator-flex-bison.dir\common.cpp.obj -c D:\Project\Compile\lab3\MiniC\common.cpp

CMakeFiles/calculator-flex-bison.dir/common.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calculator-flex-bison.dir/common.cpp.i"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\Compile\lab3\MiniC\common.cpp > CMakeFiles\calculator-flex-bison.dir\common.cpp.i

CMakeFiles/calculator-flex-bison.dir/common.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calculator-flex-bison.dir/common.cpp.s"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\Compile\lab3\MiniC\common.cpp -o CMakeFiles\calculator-flex-bison.dir\common.cpp.s

CMakeFiles/calculator-flex-bison.dir/symbol.cpp.obj: CMakeFiles/calculator-flex-bison.dir/flags.make
CMakeFiles/calculator-flex-bison.dir/symbol.cpp.obj: CMakeFiles/calculator-flex-bison.dir/includes_CXX.rsp
CMakeFiles/calculator-flex-bison.dir/symbol.cpp.obj: D:/Project/Compile/lab3/MiniC/symbol.cpp
CMakeFiles/calculator-flex-bison.dir/symbol.cpp.obj: CMakeFiles/calculator-flex-bison.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Project\Compile\lab3\MiniC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/calculator-flex-bison.dir/symbol.cpp.obj"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/calculator-flex-bison.dir/symbol.cpp.obj -MF CMakeFiles\calculator-flex-bison.dir\symbol.cpp.obj.d -o CMakeFiles\calculator-flex-bison.dir\symbol.cpp.obj -c D:\Project\Compile\lab3\MiniC\symbol.cpp

CMakeFiles/calculator-flex-bison.dir/symbol.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calculator-flex-bison.dir/symbol.cpp.i"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\Compile\lab3\MiniC\symbol.cpp > CMakeFiles\calculator-flex-bison.dir\symbol.cpp.i

CMakeFiles/calculator-flex-bison.dir/symbol.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calculator-flex-bison.dir/symbol.cpp.s"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\Compile\lab3\MiniC\symbol.cpp -o CMakeFiles\calculator-flex-bison.dir\symbol.cpp.s

CMakeFiles/calculator-flex-bison.dir/IRInst.cpp.obj: CMakeFiles/calculator-flex-bison.dir/flags.make
CMakeFiles/calculator-flex-bison.dir/IRInst.cpp.obj: CMakeFiles/calculator-flex-bison.dir/includes_CXX.rsp
CMakeFiles/calculator-flex-bison.dir/IRInst.cpp.obj: D:/Project/Compile/lab3/MiniC/IRInst.cpp
CMakeFiles/calculator-flex-bison.dir/IRInst.cpp.obj: CMakeFiles/calculator-flex-bison.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Project\Compile\lab3\MiniC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/calculator-flex-bison.dir/IRInst.cpp.obj"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/calculator-flex-bison.dir/IRInst.cpp.obj -MF CMakeFiles\calculator-flex-bison.dir\IRInst.cpp.obj.d -o CMakeFiles\calculator-flex-bison.dir\IRInst.cpp.obj -c D:\Project\Compile\lab3\MiniC\IRInst.cpp

CMakeFiles/calculator-flex-bison.dir/IRInst.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calculator-flex-bison.dir/IRInst.cpp.i"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\Compile\lab3\MiniC\IRInst.cpp > CMakeFiles\calculator-flex-bison.dir\IRInst.cpp.i

CMakeFiles/calculator-flex-bison.dir/IRInst.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calculator-flex-bison.dir/IRInst.cpp.s"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\Compile\lab3\MiniC\IRInst.cpp -o CMakeFiles\calculator-flex-bison.dir\IRInst.cpp.s

CMakeFiles/calculator-flex-bison.dir/IRCode.cpp.obj: CMakeFiles/calculator-flex-bison.dir/flags.make
CMakeFiles/calculator-flex-bison.dir/IRCode.cpp.obj: CMakeFiles/calculator-flex-bison.dir/includes_CXX.rsp
CMakeFiles/calculator-flex-bison.dir/IRCode.cpp.obj: D:/Project/Compile/lab3/MiniC/IRCode.cpp
CMakeFiles/calculator-flex-bison.dir/IRCode.cpp.obj: CMakeFiles/calculator-flex-bison.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Project\Compile\lab3\MiniC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/calculator-flex-bison.dir/IRCode.cpp.obj"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/calculator-flex-bison.dir/IRCode.cpp.obj -MF CMakeFiles\calculator-flex-bison.dir\IRCode.cpp.obj.d -o CMakeFiles\calculator-flex-bison.dir\IRCode.cpp.obj -c D:\Project\Compile\lab3\MiniC\IRCode.cpp

CMakeFiles/calculator-flex-bison.dir/IRCode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calculator-flex-bison.dir/IRCode.cpp.i"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\Compile\lab3\MiniC\IRCode.cpp > CMakeFiles\calculator-flex-bison.dir\IRCode.cpp.i

CMakeFiles/calculator-flex-bison.dir/IRCode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calculator-flex-bison.dir/IRCode.cpp.s"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\Compile\lab3\MiniC\IRCode.cpp -o CMakeFiles\calculator-flex-bison.dir\IRCode.cpp.s

CMakeFiles/calculator-flex-bison.dir/genIR.cpp.obj: CMakeFiles/calculator-flex-bison.dir/flags.make
CMakeFiles/calculator-flex-bison.dir/genIR.cpp.obj: CMakeFiles/calculator-flex-bison.dir/includes_CXX.rsp
CMakeFiles/calculator-flex-bison.dir/genIR.cpp.obj: D:/Project/Compile/lab3/MiniC/genIR.cpp
CMakeFiles/calculator-flex-bison.dir/genIR.cpp.obj: CMakeFiles/calculator-flex-bison.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Project\Compile\lab3\MiniC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/calculator-flex-bison.dir/genIR.cpp.obj"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/calculator-flex-bison.dir/genIR.cpp.obj -MF CMakeFiles\calculator-flex-bison.dir\genIR.cpp.obj.d -o CMakeFiles\calculator-flex-bison.dir\genIR.cpp.obj -c D:\Project\Compile\lab3\MiniC\genIR.cpp

CMakeFiles/calculator-flex-bison.dir/genIR.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calculator-flex-bison.dir/genIR.cpp.i"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\Compile\lab3\MiniC\genIR.cpp > CMakeFiles\calculator-flex-bison.dir\genIR.cpp.i

CMakeFiles/calculator-flex-bison.dir/genIR.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calculator-flex-bison.dir/genIR.cpp.s"
	D:\Project\Compile\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\Compile\lab3\MiniC\genIR.cpp -o CMakeFiles\calculator-flex-bison.dir\genIR.cpp.s

# Object files for target calculator-flex-bison
calculator__flex__bison_OBJECTS = \
"CMakeFiles/calculator-flex-bison.dir/calculator_lex.cpp.obj" \
"CMakeFiles/calculator-flex-bison.dir/calculator_yacc.cpp.obj" \
"CMakeFiles/calculator-flex-bison.dir/ast.cpp.obj" \
"CMakeFiles/calculator-flex-bison.dir/expr.cpp.obj" \
"CMakeFiles/calculator-flex-bison.dir/main.cpp.obj" \
"CMakeFiles/calculator-flex-bison.dir/graph.cpp.obj" \
"CMakeFiles/calculator-flex-bison.dir/common.cpp.obj" \
"CMakeFiles/calculator-flex-bison.dir/symbol.cpp.obj" \
"CMakeFiles/calculator-flex-bison.dir/IRInst.cpp.obj" \
"CMakeFiles/calculator-flex-bison.dir/IRCode.cpp.obj" \
"CMakeFiles/calculator-flex-bison.dir/genIR.cpp.obj"

# External object files for target calculator-flex-bison
calculator__flex__bison_EXTERNAL_OBJECTS =

calculator-flex-bison.exe: CMakeFiles/calculator-flex-bison.dir/calculator_lex.cpp.obj
calculator-flex-bison.exe: CMakeFiles/calculator-flex-bison.dir/calculator_yacc.cpp.obj
calculator-flex-bison.exe: CMakeFiles/calculator-flex-bison.dir/ast.cpp.obj
calculator-flex-bison.exe: CMakeFiles/calculator-flex-bison.dir/expr.cpp.obj
calculator-flex-bison.exe: CMakeFiles/calculator-flex-bison.dir/main.cpp.obj
calculator-flex-bison.exe: CMakeFiles/calculator-flex-bison.dir/graph.cpp.obj
calculator-flex-bison.exe: CMakeFiles/calculator-flex-bison.dir/common.cpp.obj
calculator-flex-bison.exe: CMakeFiles/calculator-flex-bison.dir/symbol.cpp.obj
calculator-flex-bison.exe: CMakeFiles/calculator-flex-bison.dir/IRInst.cpp.obj
calculator-flex-bison.exe: CMakeFiles/calculator-flex-bison.dir/IRCode.cpp.obj
calculator-flex-bison.exe: CMakeFiles/calculator-flex-bison.dir/genIR.cpp.obj
calculator-flex-bison.exe: CMakeFiles/calculator-flex-bison.dir/build.make
calculator-flex-bison.exe: D:/Project/Compile/CompilerTools/msys64/mingw64/lib/libcdt.dll.a
calculator-flex-bison.exe: D:/Project/Compile/CompilerTools/msys64/mingw64/lib/libgvc.dll.a
calculator-flex-bison.exe: D:/Project/Compile/CompilerTools/msys64/mingw64/lib/libcgraph.dll.a
calculator-flex-bison.exe: D:/Project/Compile/CompilerTools/msys64/mingw64/lib/libpathplan.dll.a
calculator-flex-bison.exe: CMakeFiles/calculator-flex-bison.dir/linkLibs.rsp
calculator-flex-bison.exe: CMakeFiles/calculator-flex-bison.dir/objects1.rsp
calculator-flex-bison.exe: CMakeFiles/calculator-flex-bison.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Project\Compile\lab3\MiniC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX executable calculator-flex-bison.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\calculator-flex-bison.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/calculator-flex-bison.dir/build: calculator-flex-bison.exe
.PHONY : CMakeFiles/calculator-flex-bison.dir/build

CMakeFiles/calculator-flex-bison.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\calculator-flex-bison.dir\cmake_clean.cmake
.PHONY : CMakeFiles/calculator-flex-bison.dir/clean

CMakeFiles/calculator-flex-bison.dir/depend: D:/Project/Compile/lab3/MiniC/calculator_lex.cpp
CMakeFiles/calculator-flex-bison.dir/depend: D:/Project/Compile/lab3/MiniC/calculator_lex.h
CMakeFiles/calculator-flex-bison.dir/depend: D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp
CMakeFiles/calculator-flex-bison.dir/depend: D:/Project/Compile/lab3/MiniC/calculator_yacc.h
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Project\Compile\lab3\MiniC D:\Project\Compile\lab3\MiniC D:\Project\Compile\lab3\MiniC\cmake-build-debug D:\Project\Compile\lab3\MiniC\cmake-build-debug D:\Project\Compile\lab3\MiniC\cmake-build-debug\CMakeFiles\calculator-flex-bison.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/calculator-flex-bison.dir/depend

