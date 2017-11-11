#include "../include/FileSystem.h"

#include "../include/Files.h"

FileSystem::FileSystem() {
    Directory rootDirectory("", nullptr);
}

Directory &FileSystem::getRootDirectory() const {
    return (Directory &) rootDirectory;
}