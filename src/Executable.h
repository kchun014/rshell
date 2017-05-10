#ifndef EXECUTABLE_H
#define EXECUTABLE_H
#include <string>
#include <vector>
#include "Base.h"
//Use boost library.

class Executable  : public Base {
    protected:
    std::vector<std::string> arguments;
    std::vector<char *> convertArg;
    bool success;
    //returns whether its run, sends back to connector.
    
    public:
    Executable() { };
    Executable(std::vector<std::string> args) {
        this->arguments = args;
    };
    virtual void conversion ();
    virtual bool execute ();
    virtual char *convert(const std::string & str);
};
#endif