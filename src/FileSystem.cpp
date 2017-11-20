#include "../include/FileSystem.h"

FileSystem::FileSystem() {
    Directory *root = new Directory("", nullptr);
    rootDirectory = root;
    workingDirectory = root;
}

FileSystem::~FileSystem() {
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

FileSystem& FileSystem::operator=(const FileSystem &aFileSystem) {

    if (this != &aFileSystem) {
        delete rootDirectory;
        rootDirectory= new Directory(aFileSystem.getRootDirectory());
        workingDirectory = rootDirectory;
        return *this;
    }
}


FileSystem::FileSystem(const FileSystem &aFileSystem) {
    rootDirectory= new Directory(aFileSystem.getRootDirectory());
    workingDirectory = rootDirectory;
}
