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


Directory::~Directory() {
    for (BaseFile *child : children) {
        delete &child;
    }
}

string Directory::getAbsolutePath() {
    return BaseFile::getName() + "/";
}

int Directory::getSize() {
    return 4; // FIXME
}

void Directory::addFile(BaseFile *file) {
    children.push_back(file);
}

vector<BaseFile *> Directory::getChildren() {
    return children;
}