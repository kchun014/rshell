#ifndef __RSHELL_PARSERS__
#define __RSHELL_PARSERS__
#include <sysexits.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

class Base {
    protected:
    vector<string> vArgs;
    bool success;
    public:
    Base() {}
    Base(vector<string> args) : vArgs(args) {}
    
    virtual void initialize() = 0;
    virtual bool execute() = 0;
};

class Input : public Base {
    protected: 
    vector<Base *> semis;
    vector<string> tempc;
    
    public:
    Input(vector<string> args) : Base(args) {}
    
    void initialize();
    bool execute();
};

class Semicolon : public Base {
    protected:
    vector<Base *> commands;
    vector<string> tempPush;
    vector<string> tempPush2;
    vector<int> checkPass;
    bool logicCheck;
    bool testFlag;
    bool pFlag;
    
    public:
    Semicolon(vector<string> args) : Base(args) {}
    
    void initialize();
    bool execute();
};

class Logic : public Base {//Will change to require a boolean.
    protected:
    Base* child;
    vector<char *> convertedC;
    
    public:
    Logic(vector<string> args) : Base(args) {}
    virtual void initialize();
    virtual bool execute();
    void conversion();
    char* convert(const string & str);
    void del();
};

class Execute : public Base {
    protected:
    vector<char *> convertedArgs;
    char ** convertArgP;
    
    public:
    Execute(vector<char *> args);
    
    void initialize();
    bool execute();
};

class Test : public Base {
    protected:
    int testFlag;
    
    public:
    Test(vector<string> args) : Base(args) {}
    bool fileExists();
    void initialize();
    bool execute();
};

#endif