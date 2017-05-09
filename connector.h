#include <string>
#include <vector>
#ifndef CONNECTOR_H
#define CONNECTOR_H

class Executable;

class Connector : public Base {
    //init pointer to executable to be executed, and bool on whether the process was confirmed to be executed.
    protected:
    Base * process;
    vector<string> cvec;
    bool t_f;
    
    public:
    Connector () {};
    Connector (std::vector<std::string> arguments) {
        this->cvec = args;
    }
    virtual void set_bool(bool c);
    
    //sets the executable object, using a string of arguments to be ran
    virtual void set_executable ( std::vector<std::string> cvec ) ;
    virtual bool execute ( ) = 0;
};

#endif
