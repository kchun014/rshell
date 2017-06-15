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
    
    //code functionality for parentheses.
    for(unsigned i = 0; i <= vArgs.size() - 1; i++) {
        //Parentheses
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
        //First pass to determine signs.
        if(vArgs.at(i) == "&&") {
            checkPass.push_back(1);
        }
        else if (vArgs.at(i) == "||") {
            checkPass.push_back(2);
        }
        
        if(((vArgs.at(i) != "&&") && (vArgs.at(i) != "||") && (vArgs.at(i) != "|")) || (pipeFlag)) {//If its not special, then push back, or if pipeFlag true.
            tempPush.push_back(vArgs.at(i));
        }//Else is special, so we have to deal with it., but is never entering bottom loop.
        else {//Runs if || or &&
            if(tempPush.size() != 0 && (vArgs.at(i) == "&&" || vArgs.at(i) == "||")) {//Don't push empty vector.
                Base * L = new Logic(tempPush);
                //pushes onto commands
                commands.push_back(L);
                tempPush.clear();
            }
            if(tempPush.size() != 0 && vArgs.at(i) == "|") {
                pipeFlag=true;
                tempPush.push_back(vArgs.at(i));
                continue;
            }
        }
        
        if(pipeFlag && (i == vArgs.size() || vArgs.at(i) == "&&" || vArgs.at(i) == "||" || vArgs.at(i) == ";")) {
            pipeFlag = false;
            Base * L = new Pipe(tempPush);
            commands.push_back(L);
            tempPush.clear();
        }
        //create parsing to redirect based on input >(overwrite) or >>(append)
        //use dup, dup2
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
    for(unsigned i = 0; i < commands.size(); i++) {
        if(i == 0) {
            logicCheck = commands.at(0)->execute();
        }
        else if ( ( (checkPass.at(i) == 1) && (logicCheck == true) ) || 
        ( (checkPass.at(i) == 2) && (logicCheck == false) ) )  {
            logicCheck = commands.at(i)->execute();
        }
    }
    
    return logicCheck;
}

//--------------------------------------------------------------------------
// Logic Class
//--------------------------------------------------------------------------

void Logic::initialize() {
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
/*
char* Logic::convert(const string & str) {
    char *pc = new char[str.size() + 1];//create stored memory, make sure to remove later
    strcpy(pc, str.c_str());
    return pc;
}
*/
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
    pid_t tpid;
    //Initialize child_pid, keep value for status.
    //pid_t child_pid;
    int child_status;
    //begin forking
    pid_t child_pid = fork();
    //If in child process:
    
    FILE* val;
    int save;
    int redir = 0;
    int fd;
    //Check redirect
    for(unsigned i = 0; i < convertedArgs.size(); i++) {//Parse for redirects first.
        if(*convertedArgs[i] == '<') {
            val = fopen(convertedArgs.at(convertedArgs.size()-1), "r");
            fd = fileno(val);
            save = dup(0);
            dup2(fd, 0);
            convertedArgs.at(i) = '\0';
            redir = 1;
            break;
        }
        if(*convertedArgs[i] == '>') {
            if(strcmp(convertedArgs[i], ">>") == 0) {
                cout << "I'm in baby" << endl;
                val = fopen(convertedArgs.at(convertedArgs.size()-1), "a");
            }
            else {
                val = fopen(convertedArgs.at(convertedArgs.size()-1), "w");
            }
            fd = fileno(val);
            save = dup(1);
            dup2(fd, 1);
            convertedArgs.at(i) = '\0';
            redir = 2;
            break;
        }
    }
    //
    if(child_pid == 0) {
        //Run execvp
        convertArgP = &convertedArgs[0];
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
        if(redir == 1) {
            dup2(save, 0);
        }
        else if(redir == 2) {
            dup2(save, 1);
        }
        
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

//--------------------------------------------------------------------------
// Pipe Class
//--------------------------------------------------------------------------
void Pipe:: initialize() {
    unsigned k = 0;
    //int p[2]; //For use in dup.
    while(k < vArgs.size()) {
        while(vArgs.at(k) != "|" || k < vArgs.size()) {//Parse for everything between pipes.
            cPush.push_back(vArgs.at(k));
            k++;
        }//Need to parse for " || vArgs.at(i) == "<" || vArgs.at(i) == ">>" || vArgs.at(i) == ">" ||"
        //Preserve cPushes.
        //Should deal with piping here, in order to command input/output.
        masterPush.push_back(cPush);
        cPush.clear();
        k++;
    }
    //check for ">" "<<" and "<"
    for(unsigned i = 0; i < this->masterPush.size(); i++) {
        for(unsigned j = 0; j < this->masterPush.at(i).size(); j++) {
            if(masterPush[i][j] == "<") {
                redirVals.push_back(3); // 3 == input redir
                redirArgs.push_back(masterPush.at(i).at(masterPush.at(i).size() - 1));//Push back last argument
                masterPush.at(i).at(j) = '\0';
                break;
            }
            else if(masterPush[i][j] == ">") {
                redirVals.push_back(2);//2 for non-append
                redirArgs.push_back(masterPush.at(i).at(masterPush.at(i).size() - 1));//Push back last argument
                masterPush.at(i).at(j) = '\0';
                break;
            }
            else if(masterPush[i][j] == ">>") {
                redirVals.push_back(1);// 1 for append.
                redirArgs.push_back(masterPush.at(i).at(masterPush.at(i).size() - 1));//Push back last argument
                masterPush.at(i).at(j) = '\0';
                break;
            }
        }
        if(redirVals.size() < i) {//if we havent pushed back
            redirVals.push_back(-1);
            redirArgs.push_back("");
        }
    }
    //while loop that sets the pipes as needed (input/outputs with dup)
}

bool Pipe::execute() {
    bool return_val;
    return_val = false;
    int save_in = dup(0);
    int save_out = dup(1);//Modify input/output
    for(unsigned i = 0; i < this->masterPush.size(); i++) {
        for(unsigned j = 0; j < this->masterPush.at(i).size(); j++) {
            if(redirVals.at(i) == 1 || redirVals.at(i) == 2) {
                return_val = output(redirVals.at(i), masterConvert[i].at(masterConvert.at(i).size()-1), masterConvert[i]);
            }
            else if (redirVals.at(i) == 3) {
                return_val = input(masterConvert[i].at(masterConvert.at(i).size()-1), masterConvert[i]);
            }
            else {
                return_val = rpipe(masterConvert[i]);
            }
        }
    }
    dup2(save_in, 0);
    dup2(save_out, 1);//Fix input/output
    return return_val;
}
void Pipe::conversion() {
    for(unsigned i = 0; i < this->masterPush.size(); i++) {
        for(unsigned j = 0; j < this->masterPush[i].size(); j++) {
            convertedC.push_back(convert(this->masterPush[i].at(j)));
        }
        masterConvert.push_back(convertedC);//Push to vector given.
        convertedC.clear();//Empty convertedC after
    }
}
bool Pipe::input(const char* in_file, vector<char *> conv) {
    char ** convertArgP = &conv[0];
    
    int input_fd;
    int save;
    FILE* input = fopen(in_file, "w");
    if(input != NULL) {
        input_fd = fileno(input);
        save = dup(0);
        dup2(input_fd, 0);
    }
    
    int child_status;
    pid_t tpid;
    pid_t pid = fork();
    if(!pid) {
        if (execvp(convertArgP[0], convertArgP) < 0) {
            perror("convertArgP[0]");
        }
        exit(3);
    }
    else {
        do {
            tpid = wait(&child_status);//Get child_status which is a pid.
            if(tpid != pid) { 
                cout << "Error!" << endl;
            }
        } while(tpid != pid);
        close(input_fd);
        if(input != NULL) {
            dup2(save, 0);
        }
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
bool Pipe::output(int redir_val, const char* out_file, vector<char *> conv) {
    char ** convertArgP = &conv[0];
    
    int output_fd;
    int save;
    FILE* out_val;
    if(redir_val == 1) {//Appending
        out_val = fopen(out_file, "a");
    }
    if(redir_val == 2) {//Replacing.
        out_val = fopen(out_file, "w");
    }
    if(out_val != NULL) {
        output_fd = fileno(out_val);
        save = dup(1);
        dup2(output_fd, 1);
    }
    
    int child_status;
    pid_t tpid;
    pid_t pid = fork();
    if(!pid) {
        if (execvp(convertArgP[0], convertArgP) < 0) {
            perror("convertArgP[0]");
        }
        exit(3);
    }
    else {
        do {
            tpid = wait(&child_status);//Get child_status which is a pid.
            if(tpid != pid) { 
                cout << "Error!" << endl;
            }
        } while(tpid != pid);
        int check = WEXITSTATUS(child_status);
        if(out_val != NULL) {
            dup2(save, 1);
        }
        //Check for failure status, else return true.
        if(check == 3) {
            return false;//yeah afaik.
        }
        else {
            return true;
        }
    }
}
bool Pipe::rpipe(vector<char *> conv) {
    char ** convertArgP = &conv[0];
    int child_status;
    pid_t tpid;
    int pipefd[2];
    if(pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    if(!pid) {
        dup2(pipefd[1], 1);
        close(pipefd[0]);
        if (execvp(convertArgP[0], convertArgP) < 0) {
            perror("convertArgP[0]");
        }
        exit(3);
    }
    //assuming pipe in is correct
    else {
        dup2(pipefd[0], 0);
        close(pipefd[1]);
        do {
            tpid = wait(&child_status);//Get child_status which is a pid.
            if(tpid != pid) { 
                cout << "Error!" << endl;
            }
        } while(tpid != pid);
        close(pipefd[0]);
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
