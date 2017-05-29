#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <boost/tokenizer.hpp>
#include "Evaluate.h"

using namespace std;

int main( ) {
    //bool comment = false;
    //initialize bool to keep loop going, user input string
    //then place tokenized strings into a vector to be further parsed
    bool val = true;
    string input;
    vector<string> commands;
    
    while (val) {
        cout << "€ ";
        //comment = false;
        
        getline(cin, input);
        // properly takes in two things.
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
        boost::char_separator<char> key(" ");
        tokenizer tokens(input, key);
        //Create iterators to iterate through tokens.
        tokenizer::iterator itr = tokens.begin();
        tokenizer::iterator itrEND = tokens.end();
        
        for(; itr != itrEND; ++itr)
        {
            commands.push_back(*itr);
        }
        if(commands.size() != 0)
        {
            Base * run = new Input(commands);
            run->execute();
            commands.clear();
        }
        if(input.find("done") != string::npos) {
            val = false;
            
            continue;
        }
        
    }
       
}