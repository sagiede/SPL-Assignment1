#include "../include/Files.h"

#include <string>
#include <utility>
#include <vector>
#include <iostream>

using namespace std;


//  ~~~~~~~~ BASEFILE ~~~~~~~~~
BaseFile::BaseFile(string name) : name(name) {}
BaseFile::BaseFile(const BaseFile &aBaseFile) {}
BaseFile::~BaseFile() {}
BaseFile & BaseFile :: operator=(const BaseFile & aBaseFile){}

string BaseFile::getName() const {
    return name;
}

string BaseFile::typeToString() {}

void BaseFile::setName(string newName) {
    name = newName;
}
// File
File::File(string name, int size) : BaseFile(name), size(size) {}
File::~File(){};

int File::getSize() {
    return size;
}

string File::typeToString() {
    return "FILE";
}

BaseFile *File::clone() {
    File *file = new File(getName(), size);
    return file;
}


//  ~~~~~~~~ DIRECTORY  ~~~~~~~~
Directory::Directory(string name, Directory *parent) : BaseFile(name), parent(parent) {}

Directory::~Directory() {
    clear();
}

void Directory::clear() {
    parent = nullptr;
    for (BaseFile *child : children) {
        delete child;
    }
}


Directory::Directory(const Directory &aDirectory) : BaseFile(aDirectory.getName()), parent(aDirectory.parent) {   //copy constructor

    for (BaseFile *child : aDirectory.children) {
        children.push_back(child->clone());
    }
}

BaseFile *Directory::clone() {                                  //private func
    Directory *dir = new Directory(getName(), parent);
    for (BaseFile *child : children) {
        dir->children.push_back(child->clone());
    }
    return dir;
}

Directory & Directory::operator=(const Directory &aDirectory)    //assignment = operator
{
    if (this != &aDirectory) {
        clear();
        setName(aDirectory.getName());
        parent = aDirectory.parent;
        for (BaseFile *child : aDirectory.children) {
            children.push_back(child->clone());
        }
        return *this;
    }
}


string Directory::getAbsolutePath() {
    string fullPath = getName() + "/";
    Directory *curr = getParent();
    while (curr != nullptr) {
        fullPath = curr->getName() + "/" + fullPath;
        curr = curr->getParent();
    }
    return fullPath;
}

string Directory::typeToString() {
    return "DIR";
}

BaseFile *Directory::findFileByName(string name) {
    for (BaseFile *child : getChildren()) {
        if (child->getName() == name) {
            return child;
        }
    }
    return nullptr;
};

Directory *Directory::findDirByName(string name) {
    for (BaseFile *child : getChildren()) {
        if (child->getName() == name && child->typeToString() == "DIR") {
            return (Directory *) child;
        }
    }
    return nullptr;
};

int Directory::getSize() {
    int size = 0;
    for (BaseFile *child : children) {
        size += child->getSize();
    }
    return size;
}

void Directory::addFile(BaseFile *file) {
    children.push_back(file);
}

vector<BaseFile *> Directory::getChildren() {
    return children;
}

Directory *Directory::getParent() const {
    return parent;
}

