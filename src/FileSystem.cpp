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
    if (verbose == 1 || verbose == 3)
        cout << "FileSystem::~FileSystem()" << endl;
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

FileSystem &FileSystem::operator=(const FileSystem &aFileSystem) {      //operator =
    if (verbose == 1 || verbose == 3)
        cout << "FileSystem& FileSystem::operator=(const FileSystem &aFileSystem)" << endl;
    if (this != &aFileSystem) {
        delete rootDirectory;
        rootDirectory = new Directory(*&aFileSystem.getRootDirectory());
        workingDirectory = rootDirectory;
    }
    return *this;
}


FileSystem::FileSystem(const FileSystem &aFileSystem) {                 //copy constructor
    if (verbose == 1 || verbose == 3)
        cout << "FileSystem::FileSystem(const FileSystem &aFileSystem)" << endl;
    rootDirectory = new Directory(*&aFileSystem.getRootDirectory());
    workingDirectory = rootDirectory;
}

FileSystem &FileSystem::operator=(FileSystem &&other) {                 //move assignment operator
    if (verbose == 1 || verbose == 3)
        cout << "FileSystem& FileSystem::operator=(FileSystem &&other)" << endl;
    if (this != &other) {
        delete rootDirectory;
        rootDirectory = other.rootDirectory;
        workingDirectory = rootDirectory;
        other.workingDirectory = nullptr;
        other.rootDirectory = nullptr;
    }
    return *this;
}


FileSystem::FileSystem(FileSystem &&other) : rootDirectory(other.rootDirectory) {       //move constructor
    if (verbose == 1 || verbose == 3)
        cout << "FileSystem::FileSystem(FileSystem &&other)" << endl;
    workingDirectory = rootDirectory;
    other.rootDirectory = nullptr;
    other.workingDirectory = nullptr;
}
