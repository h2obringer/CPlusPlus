Visual Studio 2013 Command Prompt Compilation:

For C code: cl /W4 main.c
For C++ code: cl /EHsc main.cpp
For projects with multiple class files, compile each seperately.
Then: link main.cc other.cc

OpenGL in Visual Studio 2013:

OpenGL .dll files have been added to the C:/dev/bin/.
C:/dev/bin has been added to the system "Path" environment variable
for the system to locate these dll files. 
OpenGL header files have been added to C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\include\
to allow for header link ups.
OpenGL library files have been added to C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\lib
to allow for the library link ups.

These dependancies must be added to the linker properties of a project if not using the Visual Studios Command Line Tool.
