#include <string>
#include <vector>
#ifndef CONNECTOR_H
#define CONNECTOR_H

class Executable;

class Connector : public Base {
    //init pointer to executable to be executed, and bool on whether the process was confirmed to be executed.
    protected:
    Base * process;
    bool t_f;
    
    public:
    virtual void set_bool(bool c);
    
    //sets the executable object, using either a string (singular command), and a vector of strings(ONLY flags)
    virtual void set_executable ( char * str, vector < const char * > svec ) ;
    
    virtual void execute ( ) = 0;
};

#endif
