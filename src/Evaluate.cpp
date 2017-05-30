#include "Evaluate.h"
//--------------------------------------------------------------------------
// Input Class
//--------------------------------------------------------------------------
void Input::initialize() {
     //parsing for semicolons
     for(unsigned i = 0; i <= vArgs.size() - 1; i++) {
         if( ( (vArgs.at(i).at(vArgs.at(i).length() - 1) == ';' ) || (( i == vArgs.size() - 1) && tempc.size() != 0) ) ) {
             if(vArgs.at(i) == ";") {
                 continue; //go to next iteration, if its a solo ';';
             }
             if((vArgs.at(i).at(vArgs.at(i).length() - 1) == ';' )) {
                tempc.push_back(vArgs.at(i).substr(0, vArgs.at(i).length() - 1));
             }
             else {
                 tempc.push_back(vArgs.at(i));
             }
             //initializes semicolons
             Base * temp = new Semicolon(tempc);
            //pushes to semis
             semis.push_back(temp);
             tempc.clear();
         }
         else {
             tempc.push_back(vArgs.at(i));//Push back otherwise all tokens.
         }
     }
}

bool Input::execute() {
    this->initialize();
    for(unsigned i = 0; i < semis.size(); i++) {
        semis.at(i)->execute();
    }
    return true;
}
//--------------------------------------------------------------------------
// Semicolon Class
//--------------------------------------------------------------------------

void Semicolon::initialize() {
    //Parses for and/or
    checkPass.push_back(0);
    pFlag = false;
    //First pass to determine signs.
    for(unsigned i = 0; i <= vArgs.size() - 1; i++) {
        if(vArgs.at(i) == "&&") {
            checkPass.push_back(1);
        }
        else if (vArgs.at(i) == "||") {
            checkPass.push_back(2);
        }

    }
    //code functionality for parentheses.
    for(unsigned i = 0; i <= vArgs.size() - 1; i++) {
        //Parentheses
        /*
        if(vArgs.at(i).size() != 0) {//if not empty.
            if(vArgs.at(i).at(0) == '(') {
                if(vArgs.at(i).at(vArgs.at(i).length() - 1) != ')') {
                    string str = vArgs.at(i).substr(1);
                    tempPush2.push_back(str);
                    pFlag = true;
                    continue;
                }

                else {//Else its something like (echo)
                    //cout << "In second" << endl;
                    pFlag = false;
                    tempPush2.push_back(vArgs.at(i).substr(1, vArgs.at(i).length() - 1));
                    Base * L = new Semicolon(tempPush2);
                    commands.push_back(L);
                    tempPush2.clear();
                    continue;
                }
            }
            else if(pFlag && !(vArgs.at(i).at(vArgs.at(i).length() - 1) == ')')) { //if flag on, but not end.
                //cout << "pflag set, end char is NOT ')'" << endl;
                tempPush2.push_back(vArgs.at(i));
                continue;
            }
            else if (pFlag) {//Checks if flag still valid, thus it ends here.
                //cout << "pflag is still valid" << endl;
                tempPush2.push_back(vArgs.at(i).substr(0, vArgs.at(i).length() - 1));
                pFlag = false;
                Base * L = new Semicolon(tempPush2);
                commands.push_back(L);
                tempPush2.clear();
                continue;
            }

        }
        */
        if(vArgs.at(i) != "&&" && vArgs.at(i) != "||") {//If its not special, then push back
            tempPush.push_back(vArgs.at(i));
        }//Else is special, so we have to deal with it., but is never entering bottom loop.
        else {//Runs if || or &&
            if(tempPush.size() != 0) {//Don't push empty vector.
                Base * L = new Logic(tempPush);
                //pushes onto commands
                commands.push_back(L);
                tempPush.clear();
            }
        }
        if (i == vArgs.size() - 1 && tempPush.size() != 0) {//Have to code, so it runs at the end as well.
            Base * L = new Logic(tempPush);
            //pushes onto commands
            commands.push_back(L);
            tempPush.clear();
        }
    }
}

bool Semicolon::execute() {
    this->initialize();
    //doesnt? enter loop? or doesnt go to hello inside zz
    for(unsigned i = 0; i < commands.size(); i++) {
        if(i == 0) {
            logicCheck = commands.at(0)->execute();
        }
        else if ( ( (checkPass.at(i) == 1) && (logicCheck) ) || ( (checkPass.at(i) == 2) && (!logicCheck) ) )  {
            logicCheck = commands.at(i)->execute();
        }
    }
    return logicCheck;
}

//--------------------------------------------------------------------------
// Logic Class
//--------------------------------------------------------------------------

void Logic::initialize() {
    //
    // cout << "In Logic:" << endl;
    // for(unsigned i = 0; i < vArgs.size(); i++) {
    //     cout << "vArgs.at(" << i << "):" << vArgs.at(i) << endl;
    // }
    // cout << "End Logic: " << endl << endl;

    //calls children's initialize functions.
    this->conversion();
    if(vArgs.at(0).at(0) == '[' || vArgs.at(0) == "test") {
        this->child = new Test(vArgs);
    }
    else {
        this->child = new Execute(convertedC);
    }

}
void Logic::conversion() {
    // vector<string>::iterator beg = arguments.begin();
    for(unsigned i = 0; i < this->vArgs.size(); i++) {
        convertedC.push_back(convert(this->vArgs.at(i)));
        //Push back char * for execvp use.
    }
}
char* Logic::convert(const string & str) {
    char *pc = new char[str.size() + 1];//create stored memory, make sure to remove later
    strcpy(pc, str.c_str());
    return pc;
}
void Logic::del() {
    for(unsigned i = 0; i < convertedC.size(); i++) {
        delete[] convertedC.at(i);//remove stored memory
    }
    convertedC.clear();//remove pointers
}
bool Logic::execute() {
    this->initialize();
    //Run child, return the status.
    bool temp = this->child->execute();
    this->del();
    return temp;
}

//--------------------------------------------------------------------------
// Execute Class
//--------------------------------------------------------------------------

Execute::Execute(vector<char *> args) {
    this->convertedArgs = args;
}
void Execute::initialize() { }
bool Execute::execute() {
    convertArgP = &convertedArgs[0];
    pid_t tpid;
    //Initialize child_pid, keep value for status.
    //pid_t child_pid;
    int child_status;
    //begin forking
    pid_t child_pid = fork();
    //If in child process:
    if(child_pid == 0) {
        //Run execvp
        execvp(this->convertArgP[0], this->convertArgP);
        perror("The following error occurred");
        //reaches here if execvp fails.
        //return 3, check for 3 after if it fails.
        _exit(3);
    }
    else {
        //in parent.
        do {
            tpid = wait(&child_status);//Get child_status which is a pid.
            if(tpid != child_pid) {
                cout << "Error!" << endl;
            }
        } while(tpid != child_pid);
        int check = WEXITSTATUS(child_status);
        //Check for failure status, else return true.
        if(check == 3) {
            return false;//yeah afaik.
        }
        else {
            return true;
        }
    }
}

//--------------------------------------------------------------------------
// Test Class
//--------------------------------------------------------------------------
void Test::initialize() {
    for(unsigned i = 0; i < vArgs.size(); i++) {
        if(vArgs.at(i) == "-e") {
            testFlag = 0;
            break;
        }
        else if(vArgs.at(i) == "-f") {
            testFlag = 1;
            break;
        }
        else if(vArgs.at(i) == "-d") {
            testFlag = 2;
            break;
        }
        else {//assume -e if nothing given.
            testFlag = 0;
        }
    }
}
bool Test::execute() {
    this->initialize();
    return this->fileExists();
}

//[ -e test/dir/file]
//Flags: -e, -f, -d, e = exists, f = is a file, d = is a directory.
//From asignment: use S_ISDIR flag and S_ISREG.


bool Test::fileExists() {
    if( access( vArgs.at(vArgs.size() - 1).c_str(), 0) == 0) {
        struct stat status;

        if((stat(vArgs.at(vArgs.size() - 1).c_str(), &status) == 0) && testFlag == 0) {
            cout << "(True)" << endl;
            return true;
        }
        if(S_ISREG(status.st_mode) && testFlag == 1) {
            cout << "(True)" << endl;
            return true;
        }
        if(S_ISDIR(status.st_mode) && testFlag == 2) {
            cout << "(True)" << endl;
            return true;
        }
        else {
            cout << "(False)" << endl;
            return false;
        }

    }
    cout << "(False)" << endl;
    return false;
}
