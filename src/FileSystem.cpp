#include "../include/FileSystem.h"
#include "../include/GlobalVariables.h"
#include <iostream>


using namespace std;

FileSystem::FileSystem() {
    Directory *root = new Directory("", nullptr);
    rootDirectory = root;
    workingDirectory = root;
}

FileSystem::~FileSystem() {                 //destructor
    cout << __FUNCTION__ << endl;
    delete rootDirectory;
}

Directory &FileSystem::getRootDirectory() const {
    return *rootDirectory;
}

Directory &FileSystem::getWorkingDirectory() const {
    return *workingDirectory;
}

void FileSystem::setWorkingDirectory(Directory *newWorkingDirectory) {
    workingDirectory = newWorkingDirectory;
}

FileSystem& FileSystem::operator=(const FileSystem &aFileSystem) {      //operator =
    cout << __FUNCTION__ << endl;
    if (this != &aFileSystem) {
        delete rootDirectory;
        rootDirectory= new Directory(*&aFileSystem.getRootDirectory());
        workingDirectory = rootDirectory;
        return *this;
    }
}


FileSystem::FileSystem(const FileSystem &aFileSystem) {                 //copy constructor
    cout << __FUNCTION__ << endl;
    rootDirectory= new Directory(*&aFileSystem.getRootDirectory());
    workingDirectory = rootDirectory;
}

FileSystem& FileSystem::operator=(FileSystem &&other) {                 //move assignment operator
    cout << __FUNCTION__ << endl;
    if (this != &other) {
        delete rootDirectory;
        rootDirectory= other.rootDirectory;
        workingDirectory = rootDirectory;
        other.workingDirectory = nullptr;
        other.rootDirectory = nullptr;
        return *this;
    }
}


FileSystem::FileSystem(FileSystem &&other) : rootDirectory(other.rootDirectory) {       //move constructor
    cout << __FUNCTION__ << endl;
    workingDirectory = rootDirectory;
    other.rootDirectory = nullptr;
    other.workingDirectory = nullptr;
}
