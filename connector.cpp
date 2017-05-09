#include <string>
#include <vector>
#include "connector.h"

virtual void set_bool(bool c) {//Set boolean flag for whether the process ran correctly.
    this->t_f = c;
}

//sets the executable object, using either a string (singular command), and a vector of strings(ONLY flags)
virtual void set_executable ( char * str, vector < const char * > svec ) {
    if ( * str == "ls" ) {
        this->process = new ls( str, svec );
    }
    if ( * str == "echo" ) {
        this->process = new echo( str, svec );
    }
    if ( * str == "mkdir" ) {
        this->process = new mkdir( str, svec );
    }
    if ( * str == "git" ) {
        this->process = new git(str, svec);
    }
    else {
        cout << "Error in parsing command." << endl;
    }
}

virtual bool execute ( ) {
    return this->process->execute( );
}
