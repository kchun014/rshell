#include <string>
#include <vector>
#include "connector.h"

virtual void set_bool(bool c) {//Set boolean flag for whether the process ran correctly.
    this->t_f = c;
}

//sets the executable object, using either a string (singular command), and if needed, a vector of strings(ONLY flags)
virtual void set_executable ( std::vector < std::string > cvec ) {
    if (*svec[0] == "ls") {
        this->process = new ls(svec[0], svec );
    }
    if (*svec[0] == "echo") {
        this->process = new echo(svec[0], svec );
    }
    if (*svec[0] == "mkdir") {
        this->process = new mkdir(svec[0], svec );
    }
    if (*svec[0] == "git") {
        this->process = new git(svec[0], svec);
    }
    else {
        cout << "Error in parsing command." << endl;
    }
}

virtual bool execute ( ) {
    this->set_executable(svec);
    return this->process->execute( );
}
