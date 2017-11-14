#include "../include/Environment.h"
#include <iostream>

using namespace std;

Environment::Environment() {};

void Environment::start() {
    string userInput;
    string commandStr;
    string args;
    while (commandStr != "exit") {
        getline(cin, userInput);
        unsigned long spacePos = userInput.find(' ');
        if (spacePos == -1) {
            commandStr = userInput;
            args = "";
        } else {
            commandStr = userInput.substr(0, spacePos);
            args = userInput.substr(spacePos + 1, userInput.length() - spacePos);
        }
        cout << "commandStr: '" << commandStr << "'" << endl;
        cout << "args: '" << args << "'" << endl;

        if (commandStr == "pwd") {
            PwdCommand command("");
            command.execute(fs);
        }
    }
    // TODO start
}

FileSystem &Environment::getFileSystem() {
    return fs;
}

void Environment::addToHistory(BaseCommand *command) {
    commandsHistory.push_back(command);
}

const vector<BaseCommand *> &Environment::getHistory() const {
    return commandsHistory;
}
