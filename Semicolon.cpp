#include <vector>
#include <string>
#include "Semicolon.h"
#include "Connector.h"

bool Semicolon::execute ()  {
    for (unsigned i = 0; i < this->args.size(); i++) {
        //Comment case, 
        andex = false;
        orex = false;
        if (this->args.at(i).at(0) == '#') {
            return 1;//comments end the attempts at execution
        }
        //Comment isn't true
        if ((this->args.at(i) != "||") && (this->args.at(i) != "&&")) {
            this->runargs.push_back(this->args.at(i));
        }
        
        if ((this->args.at(i).at(this->args.at(i).length()) - 1 ) == ';') {
            this->semiex = true;
            this->runargs.pop_back();
            this->runargs.push_back(this->args.at(i).substr(0, args.at(i).length()-2));
        }
        
        if (this->args.at(i) == "||" || args.at(i) == "&&" || semiex) {
            for(unsigned i = 0; i < runargs.size(); i++) {
                this->runargs.at(i) += "\0";
            }
            if (semiex) {//reset flags if semicolon, and only if semicolon.
                this->andex = false;
                this->orex = false;
            }
            if ((orex && !check) || (andex && check) || semiex) {
                Connector * ex = new Connector(runargs);
                this->check = ex->execute();
            }
            runargs.clear();//Clear regardless, since if you don't run you don't want the commands either.
            this->semiex = false;
        }
        if (this->args.at(i) == "||") {
            this->orex = true;
            this->andex = false;
            
        }
        else if (this->args.at(i) == "&&") {
            this->andex = true;
            this->orex = false;
        }
    }
    return true;
}
    
    