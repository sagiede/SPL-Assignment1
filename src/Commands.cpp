#include "../include/Commands.h"

#include <string>
#include <iostream>
#include "../include/FileSystem.h"

using namespace std;

BaseCommand::BaseCommand(string args) : args(args) {};

string BaseCommand::toString() {};

PwdCommand::PwdCommand(string args) : BaseCommand(args) {};

string PwdCommand::toString() { return BaseCommand::toString(); };

void PwdCommand::execute(FileSystem &fs) {
    cout << fs.getRootDirectory().getAbsolutePath() << endl;
}