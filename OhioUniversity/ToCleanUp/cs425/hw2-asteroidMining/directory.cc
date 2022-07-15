#include "directory.h"
#include <cstdlib>
// Return a list of all files in the given directory
list<string> read_directory(string path)
{
  DIR *dirp = opendir(path.c_str());
  if (dirp == NULL) {
    std::cerr << "Error opening path " << path.c_str() << " in read_directory" << std::endl;
    exit(EXIT_FAILURE);
  }
  dirent *dp;
  list <string> files;
  
  while ((dp = readdir(dirp)) != NULL) {
    files.push_back(dp->d_name);
  }
  closedir(dirp);
  return(files);
}


// Return a list of all files in the given directory
// This version checks for files with a particular extension
list<string> read_directory(string path, string extension)
{
  DIR *dirp = opendir(path.c_str());
  if (dirp == NULL) {
    std::cerr << "Error opening path " << path.c_str() << " in read_directory" << std::endl;
    exit(EXIT_FAILURE);
  }
  dirent *dp;
  list <string> files;
  
  while ((dp = readdir(dirp)) != NULL) {
    string tmp=dp->d_name;
    if ((tmp.rfind(extension)!=-1)&&
	(tmp.rfind(extension)==(tmp.length()-extension.length()))) {
      files.push_back(tmp);
    }
  }
  closedir(dirp);
  return(files);
}

// Return a list of all files in the given directory
list<string> read_directory_full(string path)
{
  DIR *dirp = opendir(path.c_str());
  if (dirp == NULL) {
    std::cerr << "Error opening path " << path.c_str() << " in read_directory" << std::endl;
    exit(EXIT_FAILURE);
  }
  dirent *dp;
  list <string> files;
  
  while ((dp = readdir(dirp)) != NULL) {
    files.push_back(path+dp->d_name);
  }
  closedir(dirp);
  return(files);
}


// Return a list of all files in the given directory
// This version checks for files with a particular extension
list<string> read_directory_full(string path, string extension)
{
  DIR *dirp = opendir(path.c_str());
  if (dirp == NULL) {
    std::cerr << "Error opening path " << path.c_str() << " in read_directory" << std::endl;
    exit(EXIT_FAILURE);
  }
  dirent *dp;
  list <string> files;
  
  while ((dp = readdir(dirp)) != NULL) {
    string tmp=dp->d_name;
    if ((tmp.rfind(extension)!=-1)&&
	(tmp.rfind(extension)==(tmp.length()-extension.length()))) {
      files.push_back(path+tmp);
    }
  }
  closedir(dirp);
  return(files);
}
