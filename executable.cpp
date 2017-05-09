#include <string>
#include <vector>
#include "EXECUTABLE_H"

Executable () {};

virtual void conversion (const std::vector<std::string> & arguments, std::vector<char*> & convertArg) {
    std::transform(arguments).begin(), arguments.end(), std::back_inserter(convertArg), convert);
}

virtual char *convert(const std::string & str) {
   char *pc = new char[str.size()+1];
   std::strcpy(pc, str.c_str());
   return pc; 
}
