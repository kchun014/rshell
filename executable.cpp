#include <string>
#include <vector>
#include "EXECUTABLE_H"

Executable ( );

Executable ( Base * process ) { 
    this->Exec = process
    
}

virtual bool execute ( ) {
    return this->Exec->execute( );
}