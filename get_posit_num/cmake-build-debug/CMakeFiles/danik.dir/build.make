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
CMAKE_SOURCE_DIR = C:\Users\79885\CLionProjects\untitled3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\79885\CLionProjects\untitled3\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\danik.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\danik.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\danik.dir\flags.make

CMakeFiles\danik.dir\danik.c.obj: CMakeFiles\danik.dir\flags.make
CMakeFiles\danik.dir\danik.c.obj: ..\danik.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\79885\CLionProjects\untitled3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/danik.dir/danik.c.obj"
	"D:\Visual Studio\VC\Tools\MSVC\14.28.29333\bin\Hostx86\x86\cl.exe" @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\danik.dir\danik.c.obj /FdCMakeFiles\danik.dir\ /FS -c C:\Users\79885\CLionProjects\untitled3\danik.c
<<

CMakeFiles\danik.dir\danik.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/danik.dir/danik.c.i"
	"D:\Visual Studio\VC\Tools\MSVC\14.28.29333\bin\Hostx86\x86\cl.exe" > CMakeFiles\danik.dir\danik.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\79885\CLionProjects\untitled3\danik.c
<<

CMakeFiles\danik.dir\danik.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/danik.dir/danik.c.s"
	"D:\Visual Studio\VC\Tools\MSVC\14.28.29333\bin\Hostx86\x86\cl.exe" @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\danik.dir\danik.c.s /c C:\Users\79885\CLionProjects\untitled3\danik.c
<<

# Object files for target danik
danik_OBJECTS = \
"CMakeFiles\danik.dir\danik.c.obj"

# External object files for target danik
danik_EXTERNAL_OBJECTS =

danik.exe: CMakeFiles\danik.dir\danik.c.obj
danik.exe: CMakeFiles\danik.dir\build.make
danik.exe: CMakeFiles\danik.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\79885\CLionProjects\untitled3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable danik.exe"
	"D:\CLion\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\danik.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- "D:\Visual Studio\VC\Tools\MSVC\14.28.29333\bin\Hostx86\x86\link.exe" /nologo @CMakeFiles\danik.dir\objects1.rsp @<<
 /out:danik.exe /implib:danik.lib /pdb:C:\Users\79885\CLionProjects\untitled3\cmake-build-debug\danik.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\danik.dir\build: danik.exe

.PHONY : CMakeFiles\danik.dir\build

CMakeFiles\danik.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\danik.dir\cmake_clean.cmake
.PHONY : CMakeFiles\danik.dir\clean

CMakeFiles\danik.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\79885\CLionProjects\untitled3 C:\Users\79885\CLionProjects\untitled3 C:\Users\79885\CLionProjects\untitled3\cmake-build-debug C:\Users\79885\CLionProjects\untitled3\cmake-build-debug C:\Users\79885\CLionProjects\untitled3\cmake-build-debug\CMakeFiles\danik.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\danik.dir\depend

