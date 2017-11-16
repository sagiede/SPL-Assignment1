#include "../include/Commands.h"
#include "../include/GlobalVariables.h"

#include <string>
#include <iostream>

using namespace std;

BaseCommand::BaseCommand(string args) : args(args) {};

string BaseCommand::toString() {};

string BaseCommand::getArgs() {
    return args;
};

Directory *BaseCommand::getToPath(FileSystem &fs, string path, bool createIfNotFound) {
    Directory *childDir;
    Directory *curr;
    string dirName;
    size_t slashPos = path.find('/');
    if (slashPos == 0) {
        curr = &fs.getRootDirectory();
        path = path.substr(1);
        slashPos = path.find('/');
    } else {
        curr = &fs.getWorkingDirectory();
    }

    while (curr != nullptr && !path.empty()) {
        if (slashPos == string::npos) {
            dirName = path;
            path = "";
        } else {
            dirName = path.substr(0, slashPos);
            path = path.substr(slashPos + 1);
        }

        if (dirName == "..") {
            childDir = curr->getParent();
        } else {
            childDir = curr->findDirByName(dirName);
            if (childDir == nullptr && createIfNotFound) {
                childDir = new Directory(dirName, curr);
                curr->addFile(childDir);
            }
        }
        curr = childDir;

        slashPos = path.find('/');
    }

    return curr;
};


// pwd
PwdCommand::PwdCommand(string args) : BaseCommand(args) {};

string PwdCommand::toString() { return "pwd"; };

void PwdCommand::execute(FileSystem &fs) {
    cout << fs.getWorkingDirectory().getAbsolutePath() << endl;
}

// cd
CdCommand::CdCommand(string args) : BaseCommand(args) {};

string CdCommand::toString() { return "cd"; };

void CdCommand::execute(FileSystem &fs) {
    Directory *curr = getToPath(fs, getArgs(), false);

    if (curr == nullptr) {
        cout << "The system cannot find the path specified" << endl;
    } else {
        fs.setWorkingDirectory(curr);
    }
}

// mkdir
MkdirCommand::MkdirCommand(string args) : BaseCommand(args) {};

string MkdirCommand::toString() { return "mkdir"; };

void MkdirCommand::execute(FileSystem &fs) {
    Directory *curr;
    string dirName;
    size_t lastSlashPos = getArgs().find_last_of('/');
    if (lastSlashPos == string::npos) {
        curr = &fs.getWorkingDirectory();
        dirName = getArgs();
    } else if (lastSlashPos == 0) {
        curr = &fs.getRootDirectory();
        dirName = getArgs().substr(1);
    } else {
        string path = getArgs().substr(0, lastSlashPos);
        dirName = getArgs().substr(lastSlashPos + 1);
        curr = getToPath(fs, path, true);
    }
    if (curr->findDirByName(dirName) == nullptr) {
        Directory *newDir = new Directory(dirName, curr);
        curr->addFile(newDir);
    } else {
        cout << "The directory already exists" << endl;
    }
}

// mkdir
MkfileCommand::MkfileCommand(string args) : BaseCommand(args) {};

string MkfileCommand::toString() { return "mkfile"; };

void MkfileCommand::execute(FileSystem &fs) {
    size_t spacePos = getArgs().find(' ');
    string filePath = getArgs().substr(0, spacePos);
    int size = stoi(getArgs().substr(spacePos + 1, getArgs().length() - spacePos - 1));

    Directory *curr;
    string fileName;
    size_t lastSlashPos = filePath.find_last_of('/');
    if (lastSlashPos == string::npos) {
        curr = &fs.getWorkingDirectory();
        fileName = filePath;
    } else if (lastSlashPos == 0) {
        curr = &fs.getRootDirectory();
        fileName = filePath.substr(1);
    } else {
        string path = filePath.substr(0, lastSlashPos);
        fileName = filePath.substr(lastSlashPos + 1);
        curr = getToPath(fs, path, false);
    }
    if (curr == nullptr) {
        cout << "The system cannot find the path specified" << endl;
    } else if (curr->findFileByName(fileName) == nullptr) {
        File *newFile = new File(fileName, size);
        curr->addFile(newFile);
    } else {
        cout << "File already exists" << endl;
    }
}

// ls
LsCommand::LsCommand(string args) : BaseCommand(args) {};

string LsCommand::toString() { return "ls"; };

void LsCommand::execute(FileSystem &fs) {
    Directory *dir;
    string dirStr = getArgs();
    if (dirStr.substr(0, 2) == "-s") {
        dir = dirStr.length() > 3 ? getToPath(fs, dirStr.substr(3), false) : &fs.getWorkingDirectory();
        if (dir == nullptr) {
            cout << "The system cannot find the path specified" << endl;
        } else {
            dir->sortBySize();
        }
    } else {
        dir = getToPath(fs, dirStr, false);
        if (dir == nullptr) {
            cout << "The system cannot find the path specified" << endl;
        } else {
            dir->sortByName();
        }
    }
    if (dir != nullptr) {
        for (BaseFile *child : dir->getChildren()) {
            cout << child->typeToString() << "\t" << child->getName() << "\t" << child->getSize() << endl;
        }
    }
}

// rename
RenameCommand::RenameCommand(string args) : BaseCommand(args) {};

string RenameCommand::toString() { return "rename"; };

void RenameCommand::execute(FileSystem &fs) {
    size_t spacePos = getArgs().find(' ');
    string filePath = getArgs().substr(0, spacePos);
    string newName = getArgs().substr(spacePos + 1, getArgs().length() - spacePos - 1);

    Directory *curr;
    string fileName;
    size_t lastSlashPos = filePath.find_last_of('/');
    if (lastSlashPos == string::npos) {
        curr = &fs.getWorkingDirectory();
        fileName = filePath;
    } else if (lastSlashPos == 0) {
        curr = &fs.getRootDirectory();
        fileName = filePath.substr(1);
    } else {
        string path = filePath.substr(0, lastSlashPos);
        fileName = filePath.substr(lastSlashPos + 1);
        curr = getToPath(fs, path, false);
    }
    if (curr == nullptr || curr->findFileByName(fileName) == nullptr) {
        cout << "No such file or directory" << endl;
    } else if (curr == &fs.getWorkingDirectory()) {
        cout << "Can’t rename the working directory" << endl;
    } else {
        curr->findFileByName(fileName)->setName(newName);
    }
}

// rm
RmCommand::RmCommand(string args) : BaseCommand(args) {};

string RmCommand::toString() { return "rm"; };

void RmCommand::execute(FileSystem &fs) {
    Directory *curr;
    string fileName;
    size_t lastSlashPos = getArgs().find_last_of('/');
    if (lastSlashPos == string::npos) {
        curr = &fs.getWorkingDirectory();
        fileName = getArgs();
    } else if (lastSlashPos == 0) {
        curr = &fs.getRootDirectory();
        fileName = getArgs().substr(1);
    } else {
        string path = getArgs().substr(0, lastSlashPos);
        fileName = getArgs().substr(lastSlashPos + 1);
        curr = getToPath(fs, path, false);
    }
    BaseFile *file = curr;
    if (curr != nullptr) {
        if (!fileName.empty()) {
            file = curr->findFileByName(fileName);
        }
    }

    if (curr == nullptr || file == nullptr) {
        cout << "No such file or directory" << endl;
    } else if (file == &fs.getRootDirectory() || file == &fs.getWorkingDirectory()) {
        cout << "Can’t remove directory" << endl;
    } else {
        curr->removeFile(file);
    }
}

// verbose
VerboseCommand::VerboseCommand(string args) : BaseCommand(args) {};

void VerboseCommand::execute(FileSystem &fs) {
    verbose = stoul(getArgs());
}

string VerboseCommand::toString() { return "verbose"; }

//Error
ErrorCommand::ErrorCommand(string args) : BaseCommand(args) {}

void ErrorCommand::execute(FileSystem &fs) {
    cout << getArgs() << ": Unknown command" << endl;
}

string ErrorCommand::toString() { return getArgs(); }


// history
HistoryCommand::HistoryCommand(string args, const vector<BaseCommand *> &refHistory)
        : BaseCommand(args), history(refHistory) {}

void HistoryCommand::execute(FileSystem &fs) {
    for (int i = 0; i < history.size(); i++) {
        cout << i << "\t" << history.at(i)->toString() << endl;
    }
}

string HistoryCommand::toString() { return "history"; }

// exec
ExecCommand::ExecCommand(string args, const vector<BaseCommand *> &refHistory)
        : BaseCommand(args), history(refHistory) {}

void ExecCommand::execute(FileSystem &fs) {
    int index = std::stoi(getArgs());
    if (index >= history.size())
        cout << "Command not found" << endl;
    else
        history.at(index)->execute(fs);
}

string ExecCommand::toString() { return "exec"; }
