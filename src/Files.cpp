#include "../include/Files.h"

#include <string>
#include <utility>
#include <vector>

using namespace std;

BaseFile::BaseFile(string name) : name(name) {}

string BaseFile::getName() const {
    return name;
}

Directory::Directory(string name, Directory *parent) : BaseFile(name), parent(parent) {}

string Directory::getAbsolutePath() {
    return getName() + "/";
}

int Directory::getSize() {
    return 4; // FIXME
}