#include "../include/Environment.h"
#include "../include/GlobalVariables.h"
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

        if (verbose == 2 || verbose == 3) {
            cout << userInput << endl;
        }

        if (commandStr == "pwd") {
            PwdCommand *command = new PwdCommand(args);
            command->execute(fs);
            addToHistory(command);
        } else if (commandStr == "cd") {
            CdCommand *command = new CdCommand(args);
            command->execute(fs);
            addToHistory(command);
        } else if (commandStr == "mkdir") {
            MkdirCommand *command = new MkdirCommand(args);
            command->execute(fs);
            addToHistory(command);
        } else if (commandStr == "mkfile") {
            MkfileCommand *command = new MkfileCommand(args);
            command->execute(fs);
            addToHistory(command);
        } else if (commandStr == "ls") {
            LsCommand *command = new LsCommand(args);
            command->execute(fs);
            addToHistory(command);
        } else if (commandStr == "rename") {
            RenameCommand *command = new RenameCommand(args);
            command->execute(fs);
            addToHistory(command);
        } else if (commandStr == "rm") {
            RmCommand *command = new RmCommand(args);
            command->execute(fs);
            addToHistory(command);
        } else if (commandStr == "verbose") {
            VerboseCommand *command = new VerboseCommand(args);
            command->execute(fs);
            addToHistory(command);
        } else if (commandStr == "history") {
            HistoryCommand *command = new HistoryCommand(args, getHistory());
            command->execute(fs);
            addToHistory(command);
        } else if (commandStr == "exec") {
            ExecCommand *command = new ExecCommand(args, getHistory());
            command->execute(fs);
            addToHistory(command);
        } else if (commandStr == "cp") {
            CpCommand *command = new CpCommand(args);
            command->execute(fs);
            addToHistory(command);
        } else if (commandStr == "mv") {
            MvCommand *command = new MvCommand(args);
            command->execute(fs);
            addToHistory(command);
        } else if (commandStr != "exit") {
            ErrorCommand *command = new ErrorCommand(commandStr);
            command->execute(fs);
            addToHistory(command);
        }
    }
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

Environment::~Environment() {                               //DESTRUCTOR
    //if (verbose == 2 | verbose ==1)
    //cout <<  << endl;
    for (BaseCommand *command : commandsHistory) {
        delete command;
    }
    commandsHistory.clear();
}
Environment& Environment::operator=(const Environment &aEnvironment) {  //opertaor =
    cout << __FUNCTION__ << endl;
    if (this != &aEnvironment) {
        for (BaseCommand *command : commandsHistory) {
            delete command;
        }
        commandsHistory.clear();
        fs = aEnvironment.fs;
        for (BaseCommand *cmnd : aEnvironment.commandsHistory) {
            commandsHistory.push_back(cmnd->clone());
        }
        return *this;
    }
}

Environment::Environment(const Environment &aEnvironment): fs(aEnvironment.fs) {    //copy constructor
    cout << __FUNCTION__ << endl;
    for (BaseCommand *cmnd : aEnvironment.commandsHistory) {
        commandsHistory.push_back(cmnd->clone());
    }
}

Environment::Environment(Environment &&other) : fs(other.fs) {              //move constructor
    cout << __FUNCTION__ << endl;
    for (BaseCommand *cmnd : other.commandsHistory) {
        commandsHistory.push_back(cmnd);
        cmnd = nullptr;
    }
    other.commandsHistory.clear();

}
Environment& Environment::operator=(Environment &&other) {              //move assignment operator
    cout << __FUNCTION__ << endl;
    if (this != &other) {
        for (BaseCommand *command : commandsHistory) {
            delete command;
        }
        commandsHistory.clear();
        fs = other.fs;
        for (BaseCommand *cmnd : other.commandsHistory) {
            commandsHistory.push_back(cmnd);
            cmnd = nullptr;
        }
        other.commandsHistory.clear();
        return *this;
    }
}

