#include "../include/Environment.h"
#include <iostream>


// ... You may not change this file

unsigned int verbose = 0;

int main(int, char **) {

  /*  Directory* root = new Directory("dir", nullptr );
    Directory* a = new Directory("a", root );
    Directory* b = new Directory("b", root );
    Directory* a1 = new Directory("a1", a );
    Directory* b1 = new Directory("b1", b );
    Directory* a2 = new Directory("a2", a1 );
    root->addFile(a);
    root->addFile(b);
    a->addFile(a1);
    b->addFile(b1);
    a1->addFile(a2);
    Directory* testPointer = b;
    *testPointer = *a;
    cout << "end" << endl;*/

    Environment env;
    env.start();



    return 0;
}
