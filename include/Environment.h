#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "FileSystem.h"
#include "Files.h"
#include "Commands.h"

#include <string>
#include <vector>

using namespace std;

class Environment {
private:
   vector<BaseCommand *> commandsHistory;
    FileSystem fs;

public:
    Environment();
    ~Environment(); // Destructor
    Environment(const Environment & aEnvironment);  //copy constructor
    Environment& operator=(const Environment &aEnvironment);    //assignment = operator
    Environment(Environment&& other);     //move constructor
    Environment& operator=(Environment &&other);   //move assignment = operator

    void start();

    FileSystem &getFileSystem(); // Get a reference to the file system
    void addToHistory(BaseCommand *command); // Add a new command to the history
    const vector<BaseCommand *> &getHistory() const; // Return a reference to the history of commands
};

#endif