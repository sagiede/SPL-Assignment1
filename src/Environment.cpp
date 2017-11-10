#include "../include/Environment.h"

Environment::Environment() {};

void Environment::start() {
// TODO start
}

FileSystem &Environment::getFileSystem() const {
//    return fs;
}

void Environment::addToHistory(BaseCommand *command) {
    commandsHistory.push_back(command);
}

const vector<BaseCommand *> &Environment::getHistory() const {
    return commandsHistory;
}
