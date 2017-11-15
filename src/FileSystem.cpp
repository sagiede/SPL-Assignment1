#include <iostream>
#include "../include/FileSystem.h"

FileSystem::FileSystem() {
    Directory* root = new Directory("", nullptr);
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