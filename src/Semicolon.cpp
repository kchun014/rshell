#include <vector>
#include <string>
#include <iostream>
#include "Semicolon.h"
#include "Connector.h"

bool Semicolon::execute ()  {
    this->orex = true;//To insure first iteration always runs
    this->andex = false;
    this->check = false;
    for (unsigned i = 0; i < args.size(); i++) {
        if ((args.at(i) != "||") && (this->args.at(i) != "&&")) {
            this->runargs.push_back(this->args.at(i));//Push back when not an operators
        }
        //If you find a semicolon, remove it, push back a version without, and continue, set flag to run.
        if (args.at(i).at(args.at(i).length() - 1) == ';') {
            this->semiex = true;
            this->runargs.pop_back();
            this->runargs.push_back(this->args.at(i).substr(0, args.at(i).length()-1));
        }
        //Checking for when it should run.
        if (args.at(i) == "||" || args.at(i) == "&&" || semiex || (i+1 == args.size())) {
            for(unsigned j = 0; j < runargs.size(); j++) {//Append strings with \0 for execvp char pointers.
                this->runargs.at(j) += '\0';
            }
            //Checks if conditions are true; if so, output.
            if((orex && !check) || (andex && check) || semiex || (i+1 == args.size())) {//First boolean check, checks for finish conditions.
                
                if ((orex && !check) || (andex && check)) {//Secondary boolean check. First one will succeed due to initial flags.
                    Connector * ex = new Connector(runargs);
                    this->check = ex->execute();
                }
            }
            else {
                check = false;//False if previous didn't run.
            }
            runargs.clear();//Clear regardless, since if you don't run you don't want the commands either.
            this->semiex = false;
        }
        if (this->args.at(i) == "||") {
            this->orex = true;
            //this->andex = false;
            
        }
        else if (this->args.at(i) == "&&") {
            this->andex = true;
            //this->orex = false;
        }
    }
    return true;
}
    
    