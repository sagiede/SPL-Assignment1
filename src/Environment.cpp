#include "../include/Environment.h"
#include <iostream>

using namespace std;

Environment::Environment() : commandsHistory(), fs() {};

void Environment::start() {
    string userInput;
    string commandStr;
    string args;
    size_t spacePos;

    while (commandStr != "exit") {
        getline(cin, userInput);
        spacePos = userInput.find(' ');
        if (spacePos == string::npos) {
            commandStr = userInput;
            args = "";
        } else {
            commandStr = userInput.substr(0, spacePos);
            args = userInput.substr(spacePos + 1, userInput.length() - spacePos - 1);
        }
        cout << "commandStr: '" << commandStr << "'" << endl;
        cout << "args: '" << args << "'" << endl;

        if (commandStr == "pwd") {
            cout << "running pwd" << endl;
            PwdCommand command("");
            command.execute(fs);
        } else if (commandStr == "mkdir") {
            cout << "running mkdir" << endl;
            MkdirCommand command(args);
            command.execute(fs);
        } else if (commandStr == "ls") {
            cout << "running ls" << endl;
            LsCommand command(args);
            command.execute(fs);
        } else {
            cout << "nothing is running" << endl;
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
