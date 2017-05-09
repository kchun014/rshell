#ifndef EXECUTABLE_H
#define EXECUTABLE_H
#include <string>
#include <vector>
//Use boost library.

class Executable  : public Base {
    protected:
    Base * Exec;
    
    std::vector< const char * > arguments;
    
    bool success = false;
    //returns whether its run, sends back to connector.
    
    public:
    
    Executable ( );
    Executable ( Base * process );
    
    virtual bool execute ( );
};
#endif