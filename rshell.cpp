#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <vector>
#include <boost/tokenizer.hpp>

using namespace std;

vector <int> parse1 ( string & input );

int main( ) {
    bool val = true;
    string input;
    vector < int > semicolons;
    vector < int > connectors;
    
    while (val) {
        
        if (input == "") {
            cout << "$ ";
        }
        
        getline(cin, input);
        typedef boost::tokenizer< boost::char_separator< char > > tokenizer;
        boost::char_separator< char > key(" ", ";#");
        tokenizer tokens(input, key);
        
        for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter) {
            cout << "<" << *tok_iter << "> ";
        }
        tokenizer::iterator tok_iter2 = tokens.begin();
        // while (*tok_iter != "||" && tok_iter != ";" && tok_iter != "&&" ) {
            
        // }
        execvp(*tok_iter2, );
    }
}

void parse(char * check, char ** argv);
void exit( bool & val ) {
    val = false;
}
