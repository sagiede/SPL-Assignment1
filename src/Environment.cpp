#include "../include/Environment.h"
#include <iostream>

using namespace std;

Environment::Environment() {};

void Environment::start() {
    string commandStr;
    string args;
    while (commandStr != "exit") {
        cin >> commandStr;
        if (commandStr == "pwd") {
            PwdCommand command("");
            command.execute(fs);
        }
    }
    // TODO start
}

FileSystem &Environment::getFileSystem() const {
    return (FileSystem &) fs;
}

void Environment::addToHistory(BaseCommand *command) {
    commandsHistory.push_back(command);
}

const vector<BaseCommand *> &Environment::getHistory() const {
    return commandsHistory;
}
