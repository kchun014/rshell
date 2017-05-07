#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <boost/tokenizer>
#include <string.h>

using namespace std;

int main( int argc, char * argv[] ) {
	execvp(argv[2], argv[2:]);
	return;
}
