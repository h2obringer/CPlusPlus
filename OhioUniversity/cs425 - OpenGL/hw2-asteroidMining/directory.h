#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <list>
using std::list;
using std::string;

// Return a list of files in the given directory.
list<string> read_directory(string path);
list<string> read_directory(string path, string extension);

// Return a list of files in the given directory.
// These return the full path to the files.
list<string> read_directory_full(string path);
list<string> read_directory_full(string path, string extension);

#endif
