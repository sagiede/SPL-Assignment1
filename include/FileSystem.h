#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include "Files.h"

class FileSystem {
private:
    Directory *rootDirectory;
    Directory *workingDirectory;
public:
    FileSystem();
    ~FileSystem();
    FileSystem(const FileSystem & aFileSystem);  //copy constructor
    FileSystem& operator=(const FileSystem &aFileSystem);    //assignment = operator
    FileSystem(FileSystem&& other);     //move constructor
    FileSystem& operator=(FileSystem &&other);   //move assignment = operator
    Directory &getRootDirectory() const; // Return reference to the root directory
    Directory &getWorkingDirectory() const; // Return reference to the working directory
    void setWorkingDirectory(Directory *newWorkingDirectory); // Change the working directory of the file system


};


#endif
