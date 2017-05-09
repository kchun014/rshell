#ifndef EXECUTABLE_H
#define EXECUTABLE_H
#include <string>
#include <vector>
//Use boost library.

class Executable  : public Base {
    protected:
    std::vector< std::string > arguments;
    std::vector< char * > convertArg;
    bool success = false;
    //returns whether its run, sends back to connector.
    
    public:
    
    Executable ( );
    virtual void conversion (arguments);
    virtual bool execute () = 0;
    virtual char *convert(const std::string & str);
};
#endif