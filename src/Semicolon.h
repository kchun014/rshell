#ifndef SEMICOLON_H
#define SEMICOLON_H
#include <vector>
#include <string>
#include "Base.h"

class Semicolon : public Base {
    protected:
    std::vector <std::string> args;
    std::vector <std::string> runargs;
    bool check;
    bool andex;
    bool orex;
    bool semiex;
    
    public:
    
    Semicolon () { };
    Semicolon (std::vector<std::string> arguments) {
        this->args = arguments;
    };
    //builds executable object to be executed
    virtual bool execute();
};
#endif