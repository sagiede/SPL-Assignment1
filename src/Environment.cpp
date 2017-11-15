#include "../include/Environment.h"
#include <iostream>

using namespace std;

Environment::Environment() {};

void Environment::start() {
    string userInput;
    string commandStr;
    string args;
    size_t spacePos;

    while (commandStr != "exit") {
        cout << fs.getWorkingDirectory().getAbsolutePath() << ">";
        getline(cin, userInput);
        spacePos = userInput.find(' ');
        if (spacePos == string::npos) {
            commandStr = userInput;
            args = "";
        } else {
            commandStr = userInput.substr(0, spacePos);
            args = userInput.substr(spacePos + 1);
        }

        if (commandStr == "pwd") {
            PwdCommand command(args);
            command.execute(fs);
        } else if (commandStr == "cd") {
            CdCommand command(args);
            command.execute(fs);
        } else if (commandStr == "mkdir") {
            MkdirCommand command(args);
            command.execute(fs);
        }  else if (commandStr == "mkfile") {
            MkfileCommand command(args);
            command.execute(fs);
        } else if (commandStr == "ls") {
            LsCommand command(args);
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
