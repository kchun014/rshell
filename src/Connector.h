#include <string>
#include <vector>
#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "Base.h"
class Executable;

class Connector : public Base {
    //init pointer to executable to be executed, and bool on whether the process was confirmed to be executed.
    protected:
    Base * process;
    std::vector<std::string> cvec;
    bool t_f;
    
    public:
    Connector () { };
    Connector(std::vector<std::string> arguments) {
        this->cvec = arguments;
    };
    //sets the executable object, using a string of arguments to be ran
    void set_executable () ;
    virtual bool execute ( );
};

#endif
