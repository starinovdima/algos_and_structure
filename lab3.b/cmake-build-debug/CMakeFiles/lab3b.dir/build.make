# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\79885\CLionProjects\LABBBB

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\79885\CLionProjects\LABBBB\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\lab3b.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\lab3b.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\lab3b.dir\flags.make

CMakeFiles\lab3b.dir\lab3b.c.obj: CMakeFiles\lab3b.dir\flags.make
CMakeFiles\lab3b.dir\lab3b.c.obj: ..\lab3b.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\79885\CLionProjects\LABBBB\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/lab3b.dir/lab3b.c.obj"
	"D:\Visual Studio\VC\Tools\MSVC\14.28.29333\bin\Hostx86\x86\cl.exe" @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\lab3b.dir\lab3b.c.obj /FdCMakeFiles\lab3b.dir\ /FS -c C:\Users\79885\CLionProjects\LABBBB\lab3b.c
<<

CMakeFiles\lab3b.dir\lab3b.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab3b.dir/lab3b.c.i"
	"D:\Visual Studio\VC\Tools\MSVC\14.28.29333\bin\Hostx86\x86\cl.exe" > CMakeFiles\lab3b.dir\lab3b.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\79885\CLionProjects\LABBBB\lab3b.c
<<

CMakeFiles\lab3b.dir\lab3b.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab3b.dir/lab3b.c.s"
	"D:\Visual Studio\VC\Tools\MSVC\14.28.29333\bin\Hostx86\x86\cl.exe" @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\lab3b.dir\lab3b.c.s /c C:\Users\79885\CLionProjects\LABBBB\lab3b.c
<<

CMakeFiles\lab3b.dir\3b_func.c.obj: CMakeFiles\lab3b.dir\flags.make
CMakeFiles\lab3b.dir\3b_func.c.obj: ..\3b_func.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\79885\CLionProjects\LABBBB\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/lab3b.dir/3b_func.c.obj"
	"D:\Visual Studio\VC\Tools\MSVC\14.28.29333\bin\Hostx86\x86\cl.exe" @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\lab3b.dir\3b_func.c.obj /FdCMakeFiles\lab3b.dir\ /FS -c C:\Users\79885\CLionProjects\LABBBB\3b_func.c
<<

CMakeFiles\lab3b.dir\3b_func.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab3b.dir/3b_func.c.i"
	"D:\Visual Studio\VC\Tools\MSVC\14.28.29333\bin\Hostx86\x86\cl.exe" > CMakeFiles\lab3b.dir\3b_func.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\79885\CLionProjects\LABBBB\3b_func.c
<<

CMakeFiles\lab3b.dir\3b_func.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab3b.dir/3b_func.c.s"
	"D:\Visual Studio\VC\Tools\MSVC\14.28.29333\bin\Hostx86\x86\cl.exe" @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\lab3b.dir\3b_func.c.s /c C:\Users\79885\CLionProjects\LABBBB\3b_func.c
<<

# Object files for target lab3b
lab3b_OBJECTS = \
"CMakeFiles\lab3b.dir\lab3b.c.obj" \
"CMakeFiles\lab3b.dir\3b_func.c.obj"

# External object files for target lab3b
lab3b_EXTERNAL_OBJECTS =

lab3b.exe: CMakeFiles\lab3b.dir\lab3b.c.obj
lab3b.exe: CMakeFiles\lab3b.dir\3b_func.c.obj
lab3b.exe: CMakeFiles\lab3b.dir\build.make
lab3b.exe: CMakeFiles\lab3b.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\79885\CLionProjects\LABBBB\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable lab3b.exe"
	"D:\CLion\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\lab3b.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- "D:\Visual Studio\VC\Tools\MSVC\14.28.29333\bin\Hostx86\x86\link.exe" /nologo @CMakeFiles\lab3b.dir\objects1.rsp @<<
 /out:lab3b.exe /implib:lab3b.lib /pdb:C:\Users\79885\CLionProjects\LABBBB\cmake-build-debug\lab3b.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\lab3b.dir\build: lab3b.exe

.PHONY : CMakeFiles\lab3b.dir\build

CMakeFiles\lab3b.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\lab3b.dir\cmake_clean.cmake
.PHONY : CMakeFiles\lab3b.dir\clean

CMakeFiles\lab3b.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\79885\CLionProjects\LABBBB C:\Users\79885\CLionProjects\LABBBB C:\Users\79885\CLionProjects\LABBBB\cmake-build-debug C:\Users\79885\CLionProjects\LABBBB\cmake-build-debug C:\Users\79885\CLionProjects\LABBBB\cmake-build-debug\CMakeFiles\lab3b.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\lab3b.dir\depend
