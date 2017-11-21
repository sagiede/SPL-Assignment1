#include "../include/Environment.h"


// ... You may not change this file

unsigned int verbose = 0;

int main(int, char **) {
    Environment env;
    env.start();
    /*CpCommand* cp1 = new CpCommand("cp1-env1");
    CdCommand* cd1 = new CdCommand("cd1-env2");

    Environment* env1 = new Environment();
    Environment* env2 = new Environment();
    env1->addToHistory(cp1);
    env2->addToHistory(cd1);
    *env1 = move(*env2);

    Environment* envCP = new Environment(move(Environment()));
    delete env1;
    delete env2;
    delete envCP;*/
    return 0;
}
