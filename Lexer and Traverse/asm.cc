#include "kind.h"
#include "lexer.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <climits>
// Use only the neeeded aspects of each namespace
using std::string;
using std::vector;
using std::endl;
using std::cerr;
using std::cin;
using std::cout;
using std::getline;
using ASM::Token;
using ASM::Lexer;

void printword(int word) {
    putchar((word >> 24) & 0xff);
    putchar((word >> 16) & 0xff);
    putchar((word >> 8) & 0xff);
    putchar(word & 0xff);
}

struct mystruct {
    string mylabel;
    int address;
};

int main(int argc, char* argv[]){
    // Nested vector representing lines of Tokens
    // Needs to be used here to cleanup in the case
    // of an exception
    vector< vector<Token*> > tokLines;
    try{
        // Create a MIPS recognizer to tokenize
        // the input lines
        Lexer lexer;
        // Tokenize each line of the input
        string line;
        while(getline(cin,line)){
            tokLines.push_back(lexer.scan(line));
        }
        // symbol table start from here
        int myaddress = 0;
        vector<mystruct *> myvector;
        vector<vector<Token*> >::iterator myit1;
        for (myit1 = tokLines.begin(); myit1 != tokLines.end(); ++myit1) {
            vector<Token* >::iterator myit2;
            for(myit2 = myit1->begin(); myit2 != myit1->end(); ++myit2){
                if ((*myit2)->toString() == "LABEL") {
                    mystruct *newstruct = new mystruct;
                    newstruct->address = myaddress;
                    string temp = (*myit2)->getLexeme();
                    int length = temp.length();
                    temp = temp.substr(0, length-1);
                    vector<mystruct* >::iterator myit50; // check duplicated
                    for (myit50 = myvector.begin(); myit50 != myvector.end(); ++ myit50) {
                        if (temp == (*myit50)->mylabel) {
                            string msg = "ERROR1";
                            throw msg;
                        }
                    }
                    newstruct->mylabel = temp;
                    myvector.push_back(newstruct);
                }
                string compare = (*myit2)->getLexeme();
                if ((compare == "beq" || compare == "bne") && ((myit2+1) != myit1->end())) {
                    myaddress = myaddress + 4;
                }
            }
        }
        
        vector<vector<Token*> >::iterator testit;
        for(testit = tokLines.begin(); testit != tokLines.end(); ++testit){
            vector<Token*>::iterator testit2;
            for(testit2 = testit->begin(); testit2 != testit->end(); ++testit2){
                if ((*testit2)->toString() == "ID") {
                    string mystr = (*testit2)->getLexeme();
                    if (mystr == "bne" || mystr == "beq") {
                        vector<Token*>::iterator myit = testit2;
                        ++myit;
                        if (myit == testit->end() || (*myit)->toString() != "REGISTER") {
                            string msg = "ERROR2";
                            throw msg;
                        }
                        if ((*myit)->toInt() > 31 || (*myit)->toInt() < 0) {
                            string msg = "ERROR3";
                            throw msg;
                        }
                        // test $s
                        ++myit;
                        if (myit == testit->end() || (*myit)->toString() != "COMMA") {
                            string msg = "ERROR4";
                            throw msg;
                        }
                        // test comma
                        ++myit;
                        if (myit == testit->end() || (*myit)->toString() != "REGISTER") {
                            string msg = "ERROR5";
                            throw msg;
                        }
                        if ((*myit)->toInt() > 31 || (*myit)->toInt() < 0) {
                            string msg = "ERROR6";
                            throw msg;
                        }
                        // test $t
                        ++myit;
                        if (myit == testit->end() || (*myit)->toString() != "COMMA") {
                            string msg = "ERROR7";
                            throw msg;
                        }
                        // test comma
                        ++myit;
                        if (myit == testit->end() || ((*myit)->toString() != "INT"
                                                      && (*myit)->toString() != "HEXINT" &&
                                                      (*myit)->toString() != "ID")) {
                            string msg = "ERROR8";
                            throw msg;
                        } else {
                            if ((*myit)->toString() == "ID") {
                                string mystring = (*myit)->getLexeme();
                                // search symbol table
                                vector<mystruct* >::iterator myit4;
                                for (myit4 = myvector.begin(); myit4 != myvector.end(); ++myit4) {
                                    if ((*myit4)->mylabel == mystring) {
                                        --myit4;
                                        break;
                                    }
                                }
                                if (myit4 == myvector.end()) {
                                    string msg = "ERROR OF UNDIFINED LABEL";
                                    throw msg;
                                } // if label not defined
                                // end search
                            } else if ((*myit)->toString() == "INT") {
                                int i = (*myit)->toInt();
                                if (i < -32768|| i > 32767) {
                                    string msg = "ERROR9";
                                    throw msg;
                                }
                            } else {
                                int i = (*myit)->toInt();
                                if ((i>>16) != 0) {
                                    string msg = "ERROR10";
                                    throw msg;
                                }
                            }
                        }
                        // test i or label
                        ++myit;
                        if (myit != testit->end()) {
                            string msg = "ERROR11";
                            throw msg;
                        }
                        break;
                    } // if bne, beq
                    if (mystr == "sw" || mystr == "lw") {
                        vector<Token*>::iterator myit = testit2;
                        ++myit;
                        int t = (*myit)->toInt();
                        if ((*myit)->toString() != "REGISTER" || t < 0 || t > 31) {
                            string msg = "ERROR";
                            throw msg;
                        }
                        ++myit;
                        ++myit;
                        int i = (*myit)->toInt();
                        if ((*myit)->toString() == "INT") {
                            if (i < -32768 || i > 32767) {
                                string msg = "ERROR";
                                throw msg;
                            }
                        } else if ((*myit)->toString() == "HEXINT") {
                            if ((i>>16) != 0) {
                                string msg = "ERROR";
                                throw msg;
                            }
                        } else {
                            string msg = "ERROR";
                            throw msg;
                        }
                        ++myit;
                        ++myit;
                        int s = (*myit)->toInt();
                        if ((*myit)->toString() != "REGISTER" || s < 0 || s > 31) {
                            string msg = "ERROR";
                            throw msg;
                        }
                    }
                    if (mystr == "jr" || mystr == "jalr") {
                        vector<Token*>::iterator myit = testit2;
                        ++myit;
                        if (myit == testit->end()) {
                            string msg = "ERROR21";
                            throw msg;
                        }
                        if ((*myit)->toString() != "REGISTER") {
                            string msg = "ERROR24";
                            throw msg;
                        }
                        int i = (*myit)->toInt();
                        if (i < 0 || i > 31) {
                            string msg = "ERROR22";
                            throw msg;
                        }
                        ++myit;
                        if (myit != testit->end()) {
                            string msg = "ERROR23";
                            throw msg;
                        }
                    }
                } // end if
            } // end for
        } // end for
        // symbol table ends here
        // Iterate over the lines of tokens and print them to standard error
        int presentaddress = 0;
        vector<vector<Token*> >::iterator it;
        for(it = tokLines.begin(); it != tokLines.end(); ++it){
            vector<Token*>::iterator it2;
            for(it2 = it->begin(); it2 != it->end(); ++it2){
                // add here
                if ((*it2)->toString() == "DOTWORD") {
                    vector<Token*>::iterator myit10 = it2; //////
                    ++myit10;
                    ++myit10;
                    if (myit10 != it->end()) {
                        string msg = "ERROR";
                        throw msg;
                    }
                    vector<Token*>::iterator myit = it2;
                    ++myit;
                    if (myit == it->end()) { // test if the line is end
                        string msg = "ERROR";
                        throw msg;
                    }
                    string mystring = (*myit)->toString();
                    if (mystring == "ID") {
                        string mystring = (*myit)->getLexeme();
                        vector<mystruct* >::iterator myit5;
                        int value;
                        for (myit5 = myvector.begin(); myit5 != myvector.end(); ++myit5) {
                            if ((*myit5)->mylabel == mystring) {
                                value = (*myit5)->address;
                                break;
                            }
                        }
                        if (myit5 == myvector.end()) {
                            string msg = "ERROR";
                            throw msg;
                        }
                        char bit1 = value >> 24;
                        char bit2 = value >> 16;
                        char bit3 = value >> 8;
                        char bit4 = value;
                        cout << bit1 << bit2 << bit3 << bit4;
                    } else if (mystring == "INT" || mystring == "HEXINT") {
                        int value = (*myit)->toInt();
                        char bit1 = value >> 24;
                        char bit2 = value >> 16;
                        char bit3 = value >> 8;
                        char bit4 = value;
                        cout << bit1 << bit2 << bit3 << bit4;
                    } else {
                        string msg = "ERROR";
                        throw msg;
                    }
                    presentaddress += 4;
                    break;
                }
                //end here
                if ((*it2)->toString() == "ID") {
                    string mystr = (*it2)->getLexeme();
                    if (mystr == "jr" || mystr == "jalr") {
                        vector<Token*>::iterator myit = it2;
                        ++myit;
                        int s = (*myit)->toInt();
                        if (s < 0 || s > 31) {
                            string msg = "JR ERROR";
                            throw msg;
                        }
                        if (mystr == "jr") {
                            int word = (0<<26) | (s<<21) | (0<<16) | (0<<11)| 8;
                            printword(word);
                        } else {
                            int word = (0<<26) | (s<<21) | (0<<16) | (0<<11)| 9;
                            printword(word);
                        }
                        presentaddress += 4;
                    }
                    if (mystr == "add" || mystr == "sub"
                        || mystr == "slt" || mystr == "sltu") {
                        vector<Token*>::iterator myit = it2;
                        ++myit;
                        int d = (*myit)->toInt();
                        ++myit; // jump dot
                        ++myit;
                        int s = (*myit)->toInt();
                        ++myit; // jump dot
                        ++myit;
                        int t = (*myit)->toInt();
                        if (mystr == "add") {
                            int word = (0<<26) | (s<<21) | (t<<16) | (d<<11)| 32;
                            printword(word);
                        } else if (mystr == "sub") {
                            int word = (0<<26) | (s<<21) | (t<<16) | (d<<11)| 34;
                            printword(word);
                        } else if (mystr == "slt") {
                            int word = (0<<26) | (s<<21) | (t<<16) | (d<<11)| 42;
                            printword(word);
                        } else {
                            int word = (0<<26) | (s<<21) | (t<<16) | (d<<11)| 43;
                            printword(word);
                        }
                        presentaddress += 4;
                    } // if add sub slt sltu
                    if (mystr == "beq" || mystr == "bne") {
                        vector<Token*>::iterator myit = it2;
                        ++myit;
                        int s = (*myit)->toInt();
                        ++myit; // jump dot
                        ++myit;
                        int t = (*myit)->toInt();
                        ++myit; // jump dot
                        ++myit;
                        int i;
                        if ((*myit)->toString() == "INT" || (*myit)->toString() == "HEXINT") {
                            i = (*myit)->toInt();
                        } else if ((*myit)->toString() == "ID") {
                            string mystring = (*myit)->getLexeme();
                            // search symbol table
                            vector<mystruct* >::iterator myit4;
                            for (myit4 = myvector.begin(); myit4 != myvector.end(); ++myit4) {
                                if ((*myit4)->mylabel == mystring) {
                                    i = (*myit4)->address;
                                    int tempaddress = i;
                                    i = ((presentaddress - i) / 4) - 1;
                                    presentaddress = tempaddress - 4;
                                    break;
                                }
                            }
                            
                        } else {
                            string msg = "ERROR13";
                            throw msg;
                        } // if not lable and not int or hexint
                        if (mystr == "beq") {
                            int word = (4<<26) | (s<<21) | (t<<16) | ( i & 0Xffff);
                            printword(word);
                        } else {
                            int word = (5<<26) | (s<<21) | (t<<16) | ( i & 0Xffff);
                            printword(word);
                        }
                        presentaddress += 4;
                        break;
                    } // beq bne
                    if (mystr == "lis" || mystr == "mflo" || mystr == "mfhi") {
                        if (mystr == "lis") {
                            vector<Token*>::iterator myit = it2;
                            ++myit;
                            int d = (*myit)->toInt();
                            int word = (0<<26) | (0<<21) | (0<<16) | (d<<11)| 20;
                            printword(word);
                        } else if (mystr == "mflo") {
                            vector<Token*>::iterator myit = it2;
                            ++myit;
                            int d = (*myit)->toInt();
                            int word = (0<<26) | (0<<21) | (0<<16) | (d<<11)| 18;
                            printword(word);
                        } else {
                            vector<Token*>::iterator myit = it2;
                            ++myit;
                            int d = (*myit)->toInt();
                            int word = (0<<26) | (0<<21) | (0<<16) | (d<<11)| 16;
                            printword(word);
                        }
                        presentaddress += 4;
                    } // end if "lis" "mflo" "mfhi"
                    if (mystr == "mult" || mystr == "multu" || mystr == "div" || mystr == "divu") {
                        if (mystr == "mult") {
                            vector<Token*>::iterator myit = it2;
                            ++myit;
                            int s = (*myit)->toInt();
                            ++myit;
                            ++myit;
                            int t = (*myit)->toInt();
                            int word = (0<<26) | (s<<21) | (t<<16) | 24;
                            printword(word);
                        } else if (mystr == "multu") {
                            vector<Token*>::iterator myit = it2;
                            ++myit;
                            int s = (*myit)->toInt();
                            ++myit;
                            ++myit;
                            int t = (*myit)->toInt();
                            int word = (0<<26) | (s<<21) | (t<<16) | 25;
                            printword(word);
                        } else if (mystr == "div") {
                            vector<Token*>::iterator myit = it2;
                            ++myit;
                            int s = (*myit)->toInt();
                            ++myit;
                            ++myit;
                            int t = (*myit)->toInt();
                            int word = (0<<26) | (s<<21) | (t<<16) | 26;
                            printword(word);
                        } else {
                            vector<Token*>::iterator myit = it2;
                            ++myit;
                            int s = (*myit)->toInt();
                            ++myit;
                            ++myit;
                            int t = (*myit)->toInt();
                            int word = (0<<26) | (s<<21) | (t<<16) | 27;
                            printword(word);
                        }
                        presentaddress += 4;
                    } // end if "mult" "multu" "div" "divu"
                    if (mystr == "sw" || mystr == "lw") {
                        if (mystr == "sw") {
                            vector<Token*>::iterator myit = it2;
                            ++myit;
                            int t = (*myit)->toInt();
                            ++myit;
                            ++myit;
                            int i = (*myit)->toInt();
                            ++myit;
                            ++myit;
                            int s = (*myit)->toInt();
                            int word = (43<<26) | (s<<21) | (t<<16) | ( i & 0Xffff);
                            printword(word);
                        } else {
                            vector<Token*>::iterator myit = it2;
                            ++myit;
                            int t = (*myit)->toInt();
                            ++myit;
                            ++myit;
                            int i = (*myit)->toInt();
                            ++myit;
                            ++myit;
                            int s = (*myit)->toInt();
                            int word = (35<<26) | (s<<21) | (t<<16) | ( i & 0Xffff);
                            printword(word);
                        }
                        presentaddress += 4;
                    } // end if sw lw
                } // end if "ID"
            } // end for loop it2
        } // end for loop it
        // delete elements in symbol table
        vector<mystruct* >::iterator myit5;
        for (myit5 = myvector.begin(); myit5 != myvector.end(); ++ myit5) {
            delete *myit5;
        }
    } catch(const string& msg){
        // If an exception occurs print the message and end the program
        cerr << msg << endl;
    }
    // Delete the Tokens that have been made
    vector<vector<Token*> >::iterator it;
    for(it = tokLines.begin(); it != tokLines.end(); ++it){
        vector<Token*>::iterator it2;
        for(it2 = it->begin(); it2 != it->end(); ++it2){
            delete *it2;
        }
    }
}

