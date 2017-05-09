#include <string>
#include <vector>
#ifndef CONNECTOR_H
#define CONNECTOR_H

class Executable;

class Connector {
    //init pointer to executable to be executed, and bool on whether the process was confirmed to be executed.
    protected:
    Executable * process;
    bool t_f;
    
    public:
    virtual void set_bool(bool c) {
        this->t_f = c;
    }
    //sets the executable object, using either a string (singular command), and a vector of strings(ONLY flags)
    virtual void set_executable ( char * str, vector < const char * > svec ) {
        if ( * str == "ls" ) {
            process = new ls( str, svec );
        }
        if ( * str == "echo" ) {
            process = new echo( str, svec );
        }
        if ( * str == "mkdir" ) {
            process = new mkdir( str, svec );
        }
        if ( * str == "ls" ) {
            process = new (str, svec);
        }
    }
};

#endif
