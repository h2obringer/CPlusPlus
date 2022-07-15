# Extensively modified by Prof. David Chelberg
# 
# last-modified: Fri Oct 14 09:03:19 2005
#
# This sample Makefile allows you to make an OpenGL application
#   whose source is exactly one .c or one .cc file under linux.
#   check the location of the X libraries on your implementation.
#
# To use this Makefile, you type:
#
#        make xxxx
#                  
# where
#       xxxx.c is the name of the file you wish to compile 
# or
#       xxxx.cc is the name of the file you wish to compile 
#       
# A binary named xxxx will be produced
# Libraries are assumed to be in the default search paths
# as are any required include files
#
#

CC = g++

LDLIBS = -L/usr/X11R6/lib -lX11 -lGL -lGLU  -lglut -lm 
#-lXi -lXmu
INCS = -I/usr/local/include/ -L/usr/lib/

all: final

objects.o: objects.cc objects.h
	$(CC) $(INCS) objects.cc -c
#g++ -I/usr/local/include/ -L/usr/lib/ objects.cc -c

final: objects.o final.cc 
	$(CC) final.cc objects.o $(INCS) $(LDLIBS) -o final

# default rules for simple c/c++ programs.
.c:
	$(CC) $@.c $(INCS) $(LDLIBS) -o $@

.cc:
	$(CC) $@.cc $(INCS) $(LDLIBS) -o $@

