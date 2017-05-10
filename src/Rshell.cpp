#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <vector>
#include <boost/tokenizer.hpp>
#include "Executable.h"
#include "Connector.h"
#include "Semicolon.h"
#include "Base.h"

using namespace std;

void set_exit(bool & val);

int main( ) {
    // initialize our value(keeps the loop going)
    //intialize input string, and vectors possessing indices of their respective symbol.
    //ie. 'connectors' holds the index of all connectors in the input string; 'semicolons' holds the indices of all semicolons, etc. 
    bool val = true;
    string input;
    vector < string > commandsList;
    bool commentflag;

    while (val) {
        cout << "€ ";
        commentflag = false;//Start flag as false;
        //continously grab line of input, parsed using boost tokenizer.
        //define the boost::tokenizer type so we dont have to rewrite that mile long signature every single time.
        getline(cin, input);
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
        boost::char_separator<char> key(" \n");//Originally separated by ; and # as well, but that would remove them, it's better to keep those in.
        tokenizer tokens(input, key);//initialize a tokenizer to convert input into tokens, separated by whitespaces.
        
        tokenizer::iterator tok_iter = tokens.begin();
        
        for(; tok_iter != tokens.end(); ++tok_iter)
        {
            string temp2 = *tok_iter;
            if (temp2.at(0) != '#' && !commentflag) {
                commandsList.push_back(temp2);
            }
            else {
                commentflag = true;
            }
            if (temp2 == "done" || temp2 == "done;" || temp2 == "Done" || temp2 == "Done;") {
                set_exit(val);
                break;
            }
            tokenizer::iterator tok_iter2 = tok_iter;//Use second iterator to see if its the end
            tok_iter2++;
            //Comment case
            if ((temp2.at(temp2.length() - 1) == ';' || tok_iter2 == tokens.end()) && val) {
                Semicolon* sem = new Semicolon(commandsList);
                sem->execute();
                commandsList.clear();//Run each semicolon one at a time.
            }
        }
        if (val == false) {
            break;
        }
        // test value: ls -a; #this is really lame; spaghetti && macaroni || echo
    }
}

void set_exit(bool & val) {
    val = false;
    cout << "exiting rshell..." << endl;
}
