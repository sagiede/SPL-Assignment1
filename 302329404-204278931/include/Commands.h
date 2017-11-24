#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <string>
#include "FileSystem.h"

using namespace std;

class BaseCommand {
private:
    string args;

public:
    BaseCommand(string args);

    string getArgs();

    virtual ~BaseCommand() = 0;

    virtual void execute(FileSystem &fs) = 0;

    virtual string toString() = 0;

    Directory *getToPath(FileSystem &fs, string path, bool createIfNotFound);

    virtual BaseCommand *clone() = 0;
};

class PwdCommand : public BaseCommand {
private:
public:
    PwdCommand(string args);

    void execute(FileSystem &fs); // Every derived class should implement this function according to the document (pdf)

    string toString();

    PwdCommand *clone();
};

class CdCommand : public BaseCommand {
private:
public:
    CdCommand(string args);

    void execute(FileSystem &fs);

    string toString();

    CdCommand *clone();
};

class LsCommand : public BaseCommand {
private:
public:
    LsCommand(string args);

    void execute(FileSystem &fs);

    string toString();

    LsCommand *clone();
};

class MkdirCommand : public BaseCommand {
private:
public:
    MkdirCommand(string args);

    void execute(FileSystem &fs);

    string toString();

    MkdirCommand *clone();
};

class MkfileCommand : public BaseCommand {
private:
public:
    MkfileCommand(string args);

    void execute(FileSystem &fs);

    string toString();

    MkfileCommand *clone();
};

class CpCommand : public BaseCommand {
private:
public:
    CpCommand(string args);

    void execute(FileSystem &fs);

    string toString();

    CpCommand *clone();
};

class MvCommand : public BaseCommand {
private:
public:
    MvCommand(string args);

    void execute(FileSystem &fs);

    string toString();

    MvCommand *clone();
};

class RenameCommand : public BaseCommand {
private:
public:
    RenameCommand(string args);

    void execute(FileSystem &fs);

    string toString();

    RenameCommand *clone();
};

class RmCommand : public BaseCommand {
private:
public:
    RmCommand(string args);

    void execute(FileSystem &fs);

    string toString();

    RmCommand *clone();
};

class HistoryCommand : public BaseCommand {
private:
    const vector<BaseCommand *> &history;
public:
    HistoryCommand(string args, const vector<BaseCommand *> &history);

    void execute(FileSystem &fs);

    string toString();

    HistoryCommand *clone();
};


class VerboseCommand : public BaseCommand {
private:
public:
    VerboseCommand(string args);

    void execute(FileSystem &fs);

    string toString();

    VerboseCommand *clone();
};

class ErrorCommand : public BaseCommand {
private:
public:
    ErrorCommand(string args);

    void execute(FileSystem &fs);

    string toString();

    ErrorCommand *clone();
};

class ExecCommand : public BaseCommand {
private:
    const vector<BaseCommand *> &history;
public:
    ExecCommand(string args, const vector<BaseCommand *> &history);

    void execute(FileSystem &fs);

    string toString();

    ExecCommand *clone();
};


#endif
