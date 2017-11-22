#include "../include/Files.h"

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include "../include/GlobalVariables.h"

using namespace std;


//  ~~~~~~~~ BASEFILE ~~~~~~~~~
BaseFile::BaseFile(string name) : name(name) {}

BaseFile::BaseFile(const BaseFile &aBaseFile) : name(aBaseFile.getName()) {}            //copy operator

BaseFile::~BaseFile() {}                                    //destructor

string BaseFile::getName() const {
    return name;
}

string BaseFile::typeToString() { return ""; }

void BaseFile::setName(string newName) {
    name = newName;
}

// File
File::File(string name, int size) : BaseFile(name), size(size) {}

File::~File() {                                                      //destructor
    if (verbose == 1 || verbose == 3)
        cout << "File::~File()" << endl;
};

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

File::File(const File &aFile) : BaseFile(aFile.getName()), size(aFile.size) {        //copy operator
    if (verbose == 1 || verbose == 3)
        cout << "File::File(const File &aFile)" << endl;
}

File &File::operator=(File &&other) {                               //move assignment operator
    if (verbose == 1 || verbose == 3)
        cout << "File& File::operator=(File &&other)" << endl;
    setName(other.getName());
    size = other.size;
    return *this;
}

File &File::operator=(const File &aFile) {                          // operator =
    if (verbose == 1 || verbose == 3)
        cout << "File& File::operator=(const File &aFile)" << endl;
    setName(aFile.getName());
    size = aFile.size;
    return *this;
}

File::File(File &&other) : BaseFile(other.getName()), size(other.size) {               //move constructor
    if (verbose == 1 || verbose == 3)
        cout << "File::File(File &&other) : BaseFile(other.getName())" << endl;
}


//  ~~~~~~~~ DIRECTORY  ~~~~~~~~
Directory::Directory(string name, Directory *parent) : BaseFile(name), children(), parent(parent) {}

Directory::~Directory() {
    if (verbose == 1 || verbose == 3)
        cout << "Directory::~Directory()" << endl;
    clear();
}

void Directory::clear() {
    parent = nullptr;
    for (BaseFile *child : children) {
        delete child;
        child = nullptr;
    }
    children.clear();
}


Directory::Directory(const Directory &aDirectory) : BaseFile(aDirectory.getName()),
                                                    children(),
                                                    parent(aDirectory.parent) {   //copy constructor
    if (verbose == 1 || verbose == 3)
        cout << "Directory::Directory(const Directory &aDirectory)" << endl;
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

Directory &Directory::operator=(const Directory &aDirectory)    //assignment = operator
{
    if (verbose == 1 || verbose == 3)
        cout << "Directory &Directory::operator=(const Directory &aDirectory)" << endl;
    if (this != &aDirectory) {
        clear();
        setName(aDirectory.getName());
        parent = aDirectory.parent;
        for (BaseFile *child : aDirectory.children) {
            children.push_back(child->clone());
        }
    }
    return *this;
}

Directory &Directory::operator=(Directory &&other) {        //move assignment = operator
    if (verbose == 1 || verbose == 3)
        cout << "Directory& Directory::operator=(Directory &&other)" << endl;
    if (this != &other) {
        clear();
        setName(other.getName());
        parent = other.parent;
        for (BaseFile *child : other.children) {
            children.push_back(child);
            child = nullptr;
        }
        other.children.clear();
        other.parent = nullptr;
    }
    return *this;
}

Directory::Directory(Directory &&other) : BaseFile(other.getName()),
                                          children(),
                                          parent(other.parent) {   //move copy constructor
    if (verbose == 1 || verbose == 3)
        cout << "Directory::Directory(Directory &&other)" << endl;
    for (BaseFile *child : other.children) {
        children.push_back(child);
        child = nullptr;
    }
    other.children.clear();
    other.parent = nullptr;
}


string Directory::getAbsolutePath() {
    string fullPath = "/" + getName();
    Directory *curr = getParent();
    while (curr != nullptr) {
        if (curr->getParent()) {
            fullPath = "/" + curr->getName() + fullPath;
        }
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

bool compareByAlphabetic(BaseFile *fileA, BaseFile *fileB) {
    return fileA->getName().compare(fileB->getName()) < 0;
}

bool compareBySize(BaseFile *fileA, BaseFile *fileB) {
    int fileASize = fileA->getSize();
    int fileBSize = fileB->getSize();

    if (fileASize == fileBSize)
        return compareByAlphabetic(fileA, fileB);
    else
        return fileASize < fileBSize;
}

void Directory::sortByName() {
    sort(children.begin(), children.end(), compareByAlphabetic);
}

void Directory::sortBySize() {
    sort(children.begin(), children.end(), compareBySize);
}

void Directory::removeFile(string name) {
    removeFile(findFileByName(name));
}

void Directory::removeFile(BaseFile *file) {
    children.erase(remove(children.begin(), children.end(), file), children.end());
    delete file;
}

void Directory::setParent(Directory *newParent) {
    parent = newParent;
}
