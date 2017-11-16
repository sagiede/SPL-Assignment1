#include "../include/Commands.h"

#include <string>
#include <iostream>

using namespace std;

BaseCommand::BaseCommand(string args) : args(args) {};

string BaseCommand::toString() {};

string BaseCommand::getArgs() {
    return args;
};

// pwd
PwdCommand::PwdCommand(string args) : BaseCommand(args) {};

string PwdCommand::toString() {    return "pwd";};

void PwdCommand::execute(FileSystem &fs) {
    cout << fs.getWorkingDirectory().getAbsolutePath() << endl;
}

// cd
CdCommand::CdCommand(string args) : BaseCommand(args) {};

string CdCommand::toString() { return "cd"; };

void CdCommand::execute(FileSystem &fs) {
    string path = getArgs();
    Directory *curr;
    size_t slashPos = path.find('/');
    if (slashPos == 0) {
        curr = &fs.getRootDirectory();
        path = path.substr(1);
        slashPos = path.find('/');
    } else {
        curr = &fs.getWorkingDirectory();
    }
    string dirName = path.substr(0, slashPos);
    while (!dirName.empty()) {
        if (slashPos == string::npos) { // TODO check tailing /
            path = "";
        }
        if (dirName == "..") {
            curr = curr->getParent();
        } else {
            curr = curr->findDirByName(dirName);
        }

        slashPos = path.find('/');
        dirName = path.substr(0, slashPos);
        path = path.substr(slashPos + 1);
    }

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
    Directory *newDir = new Directory(getArgs(), &fs.getWorkingDirectory());
    fs.getWorkingDirectory().addFile(newDir);
}

// mkfile
MkfileCommand::MkfileCommand(string args) : BaseCommand(args) {};

string MkfileCommand::toString() { return "mkfile"; };

void MkfileCommand::execute(FileSystem &fs) {
    string args = getArgs();
    size_t spacePos = args.find(' ');
    string filePath = args.substr(0, spacePos);
    int size = stoi(args.substr(spacePos + 1, args.length() - spacePos - 1));
    File *newFile = new File(filePath, size);
    fs.getWorkingDirectory().addFile(newFile);
}


// ls
LsCommand::LsCommand(string args) : BaseCommand(args) {};

string LsCommand::toString() { return "ls"; };

void LsCommand::execute(FileSystem &fs) {
    for (BaseFile *child : fs.getWorkingDirectory().getChildren()) {
        cout << child->typeToString() << "\t" << child->getName() << "\t" << child->getSize() << endl;
    }
}







//History
HistoryCommand::HistoryCommand(string args, const vector<BaseCommand *> &refHistory)
        : BaseCommand(args) , history(refHistory) {}

void HistoryCommand::execute(FileSystem &fs) {

    for(int i=0 ; i <history.size(); i++) {
        cout << i << "\t" << history.at(i)->toString() <<endl;
    }
}
string HistoryCommand::toString() { return "history"; }

//Exec
ExecCommand::ExecCommand(string args, const vector<BaseCommand *> &refHistory)
        : BaseCommand(args) , history(refHistory) {}

void ExecCommand::execute(FileSystem &fs) {
    int index = std::stoi(getArgs());
    if(index >= history.size())
        cout << "Command not found" << endl;
    else
    history.at(index)->execute(fs);
}
string ExecCommand::toString() { return "exec"; }







