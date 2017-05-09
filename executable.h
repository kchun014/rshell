#ifndef EXECUTABLE_H
#define EXECUTABLE_H
#include <string>
#include <vector>
//Use boost library.
class Executable {
    protected:
    std::vector< const std::char * > arguments;
    bool success = false;
    //returns whether its run, sends back to connector.
    
    public:
    virtual bool return_conn ( ) {
        return success;
    }
};
#endif