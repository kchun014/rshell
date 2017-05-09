#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <vector>
#include <boost/tokenizer.hpp>

char * key ( const string & str );
void exit( bool & val );

using namespace std;

int main( ) {
    // initialize our value(keeps the loop going)
    //intialize input string, and vectors possessing indices of their respective symbol.
    //ie. 'connectors' holds the index of all connectors in the input string; 'semicolons' holds the indices of all semicolons, etc. 
    bool val = true;
    string input;
    vector < int > connectors;
    vector < int > semicolons;
    vector < int > orConn;
    vector < int > andConn;
    vector < int > comment;
    vector < string > commandsList;
    bool commentary = false; //set to true, if in comment still.
    
    while (val) {
        cout << "€ ";
        
        //continously grab line of input, parsed using boost tokenizer.
        //define the boost::tokenizer type so we dont have to rewrite that mile long signature every single time.
        getline(cin, input);
        typedef boost::tokenizer< boost::char_separator< char > > tokenizer;
        boost::char_separator< char > key(" ");//Originally separated by ; and # as well, but that would remove them, it's better to keep those in.
        tokenizer tokens(input, key);//initialize a tokenizer to convert input into tokens, separated by whitespaces.
        
        //begin parsing, initialize 'i', which will be the index of specific connectors.
        int i = 0;
        for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter, ++i) {
            //Serves to parse the tokens further, with vectors.
            string temp = *tok_iter;
            cout << "<" << *tok_iter << "> ";
            if ( temp == "||") {
                orConn.push_back( i );
                connectors.push_back( i );
            }
            if ( temp == "&&" ) {
                andConn.push_back( i );
                connectors.push_back( i );
            }
            if ( temp.at( 0 ) == '#' ) {
                commentary = true;
                comment.push_back( i );
                connectors.push_back( i );
            }
            // if ( temp.at( temp.length() - 1 ) == ';') {
            //     semicolons.push_back( i );
            //     connectors.push_back( i );
            // }
        }
        
        tokenizer::iterator tok_iter2 = tokens.begin();
        string temp2 = *tok_iter2;
        while ( ( temp2.at( temp2.length( ) - 1 ) ) != ';' && ( tok_iter != tokens.end( ) ) ) {
            if( temp2 )
            commandsList.push_back( temp2 );
            tok_iter2++;
            temp2 = *tok_iter2;
        }
        
        cout << endl;
        
        // test value: ls -a; #this is really lame; spaghetti && macaroni || echo
        
        //Want to create connector vectors? or just instantiate connector pointers, based on connectors, then instantiate them as you need to. 
        //Run connector, which takes values from 
        
        
        //execvp((*tok_iter2), ( *tok_iter ).c_str());
    }
}

char * key ( const string & str ) {
   return str.c_str();
}

void exit( bool & val ) {
    val = false;
}
