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
    vector < int > connectors;
    vector < int > semicolons;
    vector < int > orConn;
    vector < int > andConn;
    vector < int > comment;
    
    while (val) {
        
        if (input == "") {
            cout << "$ ";
        }
        
        getline(cin, input);
        typedef boost::tokenizer< boost::char_separator< char > > tokenizer;
        boost::char_separator< char > key(" ");//Originally separated by ; and # as well, but that would remove them, it's better to keep those in.
        tokenizer tokens(input, key);
        int i = 0;
        for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter, ++i) {
            //Serves to parse the tokens further, with vectors.
            string temp = *tok_iter;
            //cout << "<" << *tok_iter << "> ";
            if ( temp == "||") {
                orConn.push_back( i );
            }
            if ( temp == "&&" ) {
                andConn.push_back( i );
            }
            if ( temp.at( 0 ) == '#' ) {
                comment.push_back( i );
            }
            if ( temp.at( temp.length() - 1 ) == ';') {
                semicolons.push_back( i );
            }
        }
        cout << endl;
        
        // test value: ls -a; #this is really lame; spaghetti && macaroni || echo
        for(unsigned k = 0; k < orConn.size(); k++)
        {
            cout << "orConn values: " << orConn.at(k) << " ";
            connectors.push_back( orConn.at( k ) );
        }
        
        cout << endl;
        for(unsigned k = 0; k < andConn.size(); k++)
        {
            cout << "andConn values: " << andConn.at(k) << " ";
            connectors.push_back( andConn.at( k ) );
        }
        cout << endl;
        for(unsigned k = 0; k < semicolons.size(); k++)
        {
            if ( k == 0 ) {
                cout << "semicolon values: " ;
            }
            cout << semicolons.at(k) << " ";
            connectors.push_back( semicolons.at( k ) );
        }
        cout << endl;
        for(unsigned k = 0; k < connectors.size(); k++)
        {
            if ( k == 0 ) {
                cout << "connector values: " ;
            }
            cout << connectors.at(k) << " ";
        }
        cout << endl;
        
        //Want to create connector vectors? or just instantiate connector pointers, based on connectors, then instantiate them as you need to. 
        //Run connector, which takes values from 
        
        // tokenizer::iterator tok_iter2 = tokens.begin();
        // advance(tok_iter2, orConn.at(0));
        // cout << "tok_iter2 is at:" << * tok_iter2;
        
        //string current = *tok_iter2;
        //strcpy ( pinput, current.c_str() );
        //execvp((*tok_iter2), ( *tok_iter ).c_str());
    }
}

void parse(char * check, char ** argv);
void exit( bool & val ) {
    val = false;
}
