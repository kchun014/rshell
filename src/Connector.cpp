#include <string>
#include <vector>
#include "Connector.h"
#include "Executable.h"

//sets the executable object, using either a string (singular command), and if needed, a vector of strings(ONLY flags)
void Connector::set_executable () {
    this->process = new Executable(cvec);
}

bool Connector::execute () {
    this->set_executable();
    return this->process->execute( );
}
