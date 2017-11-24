#ifndef FILES_H_
#define FILES_H_

#include <string>
#include <vector>

using namespace std;

class BaseFile {
private:
    string name;

public:
    BaseFile(string name);

    virtual ~BaseFile(); // Destructor
    BaseFile(const BaseFile &aBaseFile);  //copy constructor
    BaseFile& operator=(const BaseFile &aBaseFile);    //assignment = operator
    BaseFile(BaseFile&& other);     //move constructor
    BaseFile& operator=(BaseFile &&other);   //move assignment = operator
    string getName() const;

    void setName(string newName);

    virtual int getSize() = 0;

    virtual BaseFile *clone() = 0;

    virtual string typeToString();

};

class File : public BaseFile {
private:
    int size;

public:
    File(string name, int size); // Constructor
    ~File(); // Destructor
    File(const File &File);  //copy constructor
    File& operator=(const File &aFile);    //assignment = operator
    File(File&& other);     //move constructor
    File& operator=(File &&other);   //move assignment = operator
    BaseFile *clone();    //clone
    int getSize(); // Return the size of the file
    string typeToString();

};

class Directory : public BaseFile {
private:
    vector<BaseFile *> children;
    Directory *parent;
    void clear();   //delete directory
    virtual BaseFile *clone();    //clone


public:
    Directory(string name, Directory *parent); // Constructor
    ~Directory(); // Destructor
    Directory(const Directory &aDirectory);  //copy constructor
    Directory& operator=(const Directory &aDirectory);    //assignment = operator
    Directory(Directory&& other);     //move constructor
    Directory& operator=(Directory &&other);   //move assignment = operator


    Directory *getParent() const; // Return a pointer to the parent of this directory
    void setParent(Directory *newParent); // Change the parent of this directory
    void addFile(BaseFile *file); // Add the file to children
    void removeFile(string name); // Remove the file with the specified name from children
    void removeFile(BaseFile *file); // Remove the file from children
    void sortByName(); // Sort children by name alphabetically (not recursively)
    void sortBySize(); // Sort children by size (not recursively)
    vector<BaseFile *> getChildren(); // Return children
    int getSize(); // Return the size of the directory (recursively)
    string getAbsolutePath();  //Return the path from the root to this
    BaseFile *findFileByName(string name);
    Directory *findDirByName(string name);

    string typeToString();

};

#endif