#include <iostream>
#include "../include/FileSystem.h"

#include "../include/Files.h"

FileSystem::FileSystem() {
    Directory root("", nullptr);
    rootDirectory = &root;
    workingDirectory = &root;
}

Directory &FileSystem::getRootDirectory() const {
    return *rootDirectory;
}