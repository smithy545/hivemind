# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = D:\Apps\JetBrains\apps\CLion\ch-0\193.6015.37\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = D:\Apps\JetBrains\apps\CLion\ch-0\193.6015.37\bin\cmake\win\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Philip\CLionProjects\hivemind

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

# Include any dependencies generated for this target.
include external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\depend.make

# Include the progress variables for this target.
include external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\progress.make

# Include the compile flags for this target's objects.
include external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\flags.make

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\adler32.c.obj: external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\flags.make
external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\adler32.c.obj: ..\external\assimp-3.0.1270\contrib\zlib\adler32.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object external/assimp-3.0.1270/contrib/zlib/CMakeFiles/zlib.dir/adler32.c.obj"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\zlib.dir\adler32.c.obj /FdCMakeFiles\zlib.dir\zlib.pdb /FS -c C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\adler32.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\adler32.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/adler32.c.i"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe > CMakeFiles\zlib.dir\adler32.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\adler32.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\adler32.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/adler32.c.s"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\zlib.dir\adler32.c.s /c C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\adler32.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\compress.c.obj: external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\flags.make
external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\compress.c.obj: ..\external\assimp-3.0.1270\contrib\zlib\compress.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object external/assimp-3.0.1270/contrib/zlib/CMakeFiles/zlib.dir/compress.c.obj"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\zlib.dir\compress.c.obj /FdCMakeFiles\zlib.dir\zlib.pdb /FS -c C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\compress.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\compress.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/compress.c.i"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe > CMakeFiles\zlib.dir\compress.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\compress.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\compress.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/compress.c.s"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\zlib.dir\compress.c.s /c C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\compress.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\crc32.c.obj: external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\flags.make
external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\crc32.c.obj: ..\external\assimp-3.0.1270\contrib\zlib\crc32.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object external/assimp-3.0.1270/contrib/zlib/CMakeFiles/zlib.dir/crc32.c.obj"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\zlib.dir\crc32.c.obj /FdCMakeFiles\zlib.dir\zlib.pdb /FS -c C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\crc32.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\crc32.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/crc32.c.i"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe > CMakeFiles\zlib.dir\crc32.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\crc32.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\crc32.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/crc32.c.s"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\zlib.dir\crc32.c.s /c C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\crc32.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\deflate.c.obj: external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\flags.make
external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\deflate.c.obj: ..\external\assimp-3.0.1270\contrib\zlib\deflate.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object external/assimp-3.0.1270/contrib/zlib/CMakeFiles/zlib.dir/deflate.c.obj"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\zlib.dir\deflate.c.obj /FdCMakeFiles\zlib.dir\zlib.pdb /FS -c C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\deflate.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\deflate.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/deflate.c.i"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe > CMakeFiles\zlib.dir\deflate.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\deflate.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\deflate.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/deflate.c.s"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\zlib.dir\deflate.c.s /c C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\deflate.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\inffast.c.obj: external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\flags.make
external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\inffast.c.obj: ..\external\assimp-3.0.1270\contrib\zlib\inffast.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object external/assimp-3.0.1270/contrib/zlib/CMakeFiles/zlib.dir/inffast.c.obj"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\zlib.dir\inffast.c.obj /FdCMakeFiles\zlib.dir\zlib.pdb /FS -c C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\inffast.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\inffast.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/inffast.c.i"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe > CMakeFiles\zlib.dir\inffast.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\inffast.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\inffast.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/inffast.c.s"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\zlib.dir\inffast.c.s /c C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\inffast.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\inflate.c.obj: external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\flags.make
external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\inflate.c.obj: ..\external\assimp-3.0.1270\contrib\zlib\inflate.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object external/assimp-3.0.1270/contrib/zlib/CMakeFiles/zlib.dir/inflate.c.obj"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\zlib.dir\inflate.c.obj /FdCMakeFiles\zlib.dir\zlib.pdb /FS -c C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\inflate.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\inflate.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/inflate.c.i"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe > CMakeFiles\zlib.dir\inflate.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\inflate.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\inflate.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/inflate.c.s"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\zlib.dir\inflate.c.s /c C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\inflate.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\inftrees.c.obj: external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\flags.make
external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\inftrees.c.obj: ..\external\assimp-3.0.1270\contrib\zlib\inftrees.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object external/assimp-3.0.1270/contrib/zlib/CMakeFiles/zlib.dir/inftrees.c.obj"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\zlib.dir\inftrees.c.obj /FdCMakeFiles\zlib.dir\zlib.pdb /FS -c C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\inftrees.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\inftrees.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/inftrees.c.i"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe > CMakeFiles\zlib.dir\inftrees.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\inftrees.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\inftrees.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/inftrees.c.s"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\zlib.dir\inftrees.c.s /c C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\inftrees.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\trees.c.obj: external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\flags.make
external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\trees.c.obj: ..\external\assimp-3.0.1270\contrib\zlib\trees.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object external/assimp-3.0.1270/contrib/zlib/CMakeFiles/zlib.dir/trees.c.obj"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\zlib.dir\trees.c.obj /FdCMakeFiles\zlib.dir\zlib.pdb /FS -c C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\trees.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\trees.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/trees.c.i"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe > CMakeFiles\zlib.dir\trees.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\trees.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\trees.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/trees.c.s"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\zlib.dir\trees.c.s /c C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\trees.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\zutil.c.obj: external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\flags.make
external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\zutil.c.obj: ..\external\assimp-3.0.1270\contrib\zlib\zutil.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object external/assimp-3.0.1270/contrib/zlib/CMakeFiles/zlib.dir/zutil.c.obj"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\zlib.dir\zutil.c.obj /FdCMakeFiles\zlib.dir\zlib.pdb /FS -c C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\zutil.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\zutil.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/zutil.c.i"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe > CMakeFiles\zlib.dir\zutil.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\zutil.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\zutil.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/zutil.c.s"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\zlib.dir\zutil.c.s /c C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib\zutil.c
<<
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

# Object files for target zlib
zlib_OBJECTS = \
"CMakeFiles\zlib.dir\adler32.c.obj" \
"CMakeFiles\zlib.dir\compress.c.obj" \
"CMakeFiles\zlib.dir\crc32.c.obj" \
"CMakeFiles\zlib.dir\deflate.c.obj" \
"CMakeFiles\zlib.dir\inffast.c.obj" \
"CMakeFiles\zlib.dir\inflate.c.obj" \
"CMakeFiles\zlib.dir\inftrees.c.obj" \
"CMakeFiles\zlib.dir\trees.c.obj" \
"CMakeFiles\zlib.dir\zutil.c.obj"

# External object files for target zlib
zlib_EXTERNAL_OBJECTS =

external\assimp-3.0.1270\contrib\zlib\zlibd.lib: external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\adler32.c.obj
external\assimp-3.0.1270\contrib\zlib\zlibd.lib: external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\compress.c.obj
external\assimp-3.0.1270\contrib\zlib\zlibd.lib: external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\crc32.c.obj
external\assimp-3.0.1270\contrib\zlib\zlibd.lib: external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\deflate.c.obj
external\assimp-3.0.1270\contrib\zlib\zlibd.lib: external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\inffast.c.obj
external\assimp-3.0.1270\contrib\zlib\zlibd.lib: external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\inflate.c.obj
external\assimp-3.0.1270\contrib\zlib\zlibd.lib: external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\inftrees.c.obj
external\assimp-3.0.1270\contrib\zlib\zlibd.lib: external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\trees.c.obj
external\assimp-3.0.1270\contrib\zlib\zlibd.lib: external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\zutil.c.obj
external\assimp-3.0.1270\contrib\zlib\zlibd.lib: external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\build.make
external\assimp-3.0.1270\contrib\zlib\zlibd.lib: external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking C static library zlibd.lib"
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	$(CMAKE_COMMAND) -P CMakeFiles\zlib.dir\cmake_clean_target.cmake
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	C:\PROGRA~2\MICROS~2\2017\COMMUN~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\link.exe /lib /nologo /machine:X86 /out:zlibd.lib @CMakeFiles\zlib.dir\objects1.rsp 
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug

# Rule to build all files generated by this target.
external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\build: external\assimp-3.0.1270\contrib\zlib\zlibd.lib

.PHONY : external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\build

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\clean:
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib
	$(CMAKE_COMMAND) -P CMakeFiles\zlib.dir\cmake_clean.cmake
	cd C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug
.PHONY : external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\clean

external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\Philip\CLionProjects\hivemind C:\Users\Philip\CLionProjects\hivemind\external\assimp-3.0.1270\contrib\zlib C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib C:\Users\Philip\CLionProjects\hivemind\cmake-build-debug\external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : external\assimp-3.0.1270\contrib\zlib\CMakeFiles\zlib.dir\depend

