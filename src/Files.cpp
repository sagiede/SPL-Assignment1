#include "../include/Files.h"

#include <string>
#include <utility>
#include <vector>

using namespace std;


//  ~~~~~~~~ BASEFILE ~~~~~~~~~
BaseFile::BaseFile(string name) : name(name) {}
BaseFile::BaseFile(const BaseFile &aBaseFile) {}
BaseFile::~BaseFile() {}
//BaseFile & BaseFile :: operator=(const BaseFile & aBaseFile){}

string BaseFile::getName() const {
    return name;
}

//  ~~~~~~~~ DIRECTORY  ~~~~~~~~
Directory::Directory(string name, Directory* parent) : BaseFile(name), parent(parent) {}

Directory::~Directory() {                   //destructor
    for (BaseFile* child : children) {
        delete child;
    }
}

Directory:: Directory(const Directory &aDirectory)  : BaseFile (aDirectory) {   //copy constructor

    for (BaseFile* child : aDirectory.children) {
        children.push_back(child->clone());
    }
}

BaseFile* Directory::clone() {                                  //private func
    Directory* dir = new Directory(getName(),parent);
    for (BaseFile* child : children) {
        dir->children.push_back(child->clone());
    }
    return dir;
}

/*Directory & Directory :: operator=(const Directory & aDirectory)    //assignment = operator
    {
    if(this != &aDirectory){
        setName(aDirectory.getName());
        parent = aDirectory.parent;
        for (BaseFile* child : children) {
            delete child;
        }
        for (BaseFile* child : aDirectory.children) {
            children.push_back(child->clone());
        }
        return *this;
    }
}
*/
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
