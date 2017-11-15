#include "../include/Commands.h"

#include <string>
#include <iostream>

using namespace std;

BaseCommand::BaseCommand(string args) : args(args) {};

string BaseCommand::toString() {};

string BaseCommand::getArgs() {
    return args;
};

// PwdCommand
PwdCommand::PwdCommand(string args) : BaseCommand(args) {};

string PwdCommand::toString() { return BaseCommand::toString(); };

void PwdCommand::execute(FileSystem& fs) {
    cout << fs.getRootDirectory().getAbsolutePath() << endl;
}

// Mkdir
MkdirCommand::MkdirCommand(string args) : BaseCommand(args) {};

string MkdirCommand::toString() { return BaseCommand::toString(); };

void MkdirCommand::execute(FileSystem &fs) {
    Directory *newDir = new Directory(getArgs(), &fs.getWorkingDirectory());
    fs.getWorkingDirectory().addFile(newDir);
}

// ls
LsCommand::LsCommand(string args) : BaseCommand(args) {};

string LsCommand::toString() { return BaseCommand::toString(); };

void LsCommand::execute(FileSystem& fs) {
    for(BaseFile *child : fs.getWorkingDirectory().getChildren()) {
        cout << child->getName() << endl;
    }
}

