#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include "Executable.h"
#include <iostream>
using namespace std;

void Executable::conversion() {
    // vector<string>::iterator beg = arguments.begin();
    for(unsigned i = 0; i < this->arguments.size(); i++) {
        convertArg.push_back(convert(this->arguments.at(i)));
    }
}

char* Executable::convert (const string & str) {
    char *pc = new char[str.size() + 1];
    strcpy(pc, str.c_str());
    return pc;
}

bool Executable::execute() {
    conversion();
    int status;
    char ** convertArgP = &convertArg[0];
    pid_t pid = fork();
    if (pid == -1) {
       cout << "Error forking!" << endl;
       return false;
    }
    else if (pid == 0) {
        if(execvp(convertArgP[0], convertArgP) == -1) {
            perror("exec");
            return false;
        }
    }
    else {//Parent
        wait(&status); 
        for(unsigned i = 0; i < convertArg.size(); i++) {
            delete[] convertArg[i];
        }
        if (status == -1) //If child fails
        {
            return false;
        }
        else {
            return true;
        }
    }
    return true;
}