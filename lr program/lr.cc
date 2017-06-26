//
//  lr.cpp
//  A7
//
//  Created by Siyuan Guo on 2016-11-07.
//  Copyright © 2016 Siyuan Guo. All rights reserved.
//
#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

struct mystruct {
    int index1;
    string state;
    string operation;
    int index2;
};

struct converse {
    int num_delete;
    string first;
};

string *rules;

mystruct **transitions;

string startrule; // the rule contain the start state

string startsymbol; // the string of start state

converse **converserule; // store each rule's (length - 1) and first element

int numRules;

int numTransitions;

//Skip the grammar part of the input.
void skipLine(istream &in) {
    string s;
    getline(in, s);
}



string trim(const string &str);

void skipGrammar(istream &in) {
    int i, numTerm, numNonTerm, numStates;
    
    // read the number of terminals and move to the next line
    in >> numTerm;
    skipLine(in);
    
    // skip the lines containing the terminals
    for (i = 0; i < numTerm; i++) {
        skipLine(in);
    }
    
    // read the number of non-terminals and move to the next line
    in >> numNonTerm;
    skipLine(in);
    
    // skip the lines containing the non-terminals
    for (i = 0; i < numNonTerm; i++) {
        skipLine(in);
    }
    
    // skip the line containing the start symbol
    getline(in, startsymbol);
    startsymbol = trim(startsymbol);
    
    // read the number of rules and move to the next line
    in >> numRules;
    skipLine(in);
    
    rules = new string[numRules];
    converserule = new converse *[numRules];
    
    // skip the lines containing the production rules
    for (i = 0; i < numRules; i++) {
        string s;
        getline(in, s);
        s = trim(s);
        rules[i] = s;
        converse *mynew = new converse;
        stringstream ss(rules[i]);
        int tempi = 0;
        string temps;
        ss >> temps;
        mynew->first = temps;
        while (ss >> temps) {
            ++tempi;
        }
        mynew->num_delete = tempi;
        converserule[i] = mynew;
    }
    
    in >> numStates;
    skipLine(in);
    
    // use array to store transitions
    in >> numTransitions;
    transitions = new mystruct *[numTransitions];
    skipLine(in);
    
    for (i = 0; i < numTransitions; i++) {
        string s;
        getline(in, s);
        s = trim(s);
        stringstream ss(s);
        int tempint;
        string tempstring;
        mystruct *tempstruct = new mystruct;
        ss >> tempint;
        tempstruct->index1 = tempint;
        ss >> tempstring;
        tempstruct->state = tempstring;
        ss >> tempstring;
        tempstruct->operation = tempstring;
        ss >> tempint;
        tempstruct->index2 = tempint;
        transitions[i] = tempstruct;
    }
    
    for (int i = 0; i < numRules; ++i) {
        if (converserule[i]->first == startsymbol) {
            startrule = rules[i];
        }
    }
}



string trim(const string &str) {
    size_t begin = str.find_first_not_of(" \t\n");
    if (begin == string::npos) return "";
    
    size_t end = str.find_last_not_of(" \t\n");
    
    return str.substr(begin, end - begin + 1);
}

// test if there is index1==c in transitions
bool checkindex(int c) {
    int i = 0;
    for (; i < numTransitions; ++i) {
        if (transitions[i]->index1 == c) {
            break;
        }
    }
    if (i == numTransitions) {
        return false;
    } else {
        return true;
    }
}

// test if there is corresponding index1 and state
bool checkboth(int b, string a) {
    int i = 0;
    for (;i < numTransitions; ++i) {
        if (transitions[i]->index1 == b) {
            if (transitions[i]->state == a) {
                break;
            } // endif
        } // endif
    } // endfor
    if (i == numTransitions) {
        return false;
    } else {
        return true;
    }
}

// return the index of the specific index1 corresponds to state
int getindex(int b, string a) {
    int i = 0;
    for (;i < numTransitions; ++i) {
        if (transitions[i]->index1 == b) {
            if (transitions[i]->state == a) {
                break;
            } // endif
        } // endif
    } // endfor
    return i;
}




int main() {
    skipGrammar(std::cin);
    
    string inputstring;
    int inputlength = 0;
    
    vector<string> input;
    while (getline(std::cin, inputstring)) {
        inputstring = trim(inputstring);
        stringstream ss(inputstring);
        string c;
        while (ss >> c) {
            input.push_back(c);
            ++inputlength;
        }
    }
    vector<string>::iterator inputit;
    inputit = input.begin(); //让inputit指向input里的第一个
    
    vector<string> mystack; // stack of map
    vector<int> mystate;
    vector<string>::iterator stackindex;
    vector<int>::iterator stateindex;
    int readnum = 1; // 反应读取的次数
    try {
        
        int statenum = 0;
        for (inputit = input.begin(); inputit != input.end();) {
            if (!checkindex(statenum)) {
                break; //这里应该直接退出loop
            }
            if (!checkboth(statenum, *(inputit))) { // not correct
                //cerr << statenum << endl;
                //cerr << *(inputit) << endl;
                throw readnum; //改过了
            }
            
            
            int index = getindex(statenum, *(inputit));
            string ope = transitions[index]->operation;
            if(ope == "shift") {                 // input one element
                //mystack[*(inputit)] = statenum;
                mystack.push_back(*(inputit));
                mystate.push_back(statenum);
                ++inputit;
                ++readnum;
            }
            statenum = transitions[index]->index2;
            if (!checkindex(statenum)) {
                break; //这里应该直接退出loop
            }
            //cerr << ope << endl;
            //cerr << statenum << endl;
            //不用改
            string temps;
            int tempi;
            if (ope == "reduce") {
                while (1) {
                    cout << rules[statenum] << endl;
                    temps = converserule[statenum]->first;
                    tempi = converserule[statenum]->num_delete;
                    if (tempi == 0) {
                        stackindex = mystack.end();
                        stateindex = mystate.end();
                        --stackindex;
                        --stateindex;
                        int tempindex = getindex(*(stateindex), *(stackindex));
                        statenum = transitions[tempindex]->index2;
                        mystack.push_back(temps);
                        mystate.push_back(statenum);
                        
                    } else {
                        for (int i = 0; i < tempi; ++i) {
                            stateindex = mystate.end();
                            --stateindex;
                            statenum = *(stateindex);
                            mystack.pop_back();
                            mystate.pop_back();
                        }
                        stackindex = mystack.end();
                        stateindex = mystate.end();
                        --stackindex;
                        --stateindex;
                        //cerr << *(stateindex) << endl;
                        //cerr << *(stackindex) << endl;
                        mystack.push_back(temps);
                        mystate.push_back(statenum);
                    }
                    if (!checkindex(statenum)) {
                        break; //这里应该直接退出loop
                    }
                    if (!checkboth(statenum, temps)) { // not correct
                        throw (readnum); //改过了
                    }
                    //cerr << statenum << endl;
                    //cerr << temps << endl;
                    index = getindex(statenum, temps);
                    string innerope = transitions[index]->operation;
                    if (innerope == "shift") {
                        statenum = transitions[index]->index2;
                        break;
                    }
                    
                } // while loop
                
            } else { // ope == "shift"
            }
            
        }
        cout << startrule << endl;
    } catch(const int& msg){
        cerr << "ERROR at " << msg << endl;
    }
    
    // this is delete
    
    delete [] rules; // delete rules
    for (int i = 0; i < numTransitions; ++i) {
        delete transitions[i];
    }
    delete [] transitions; // delete transitions
    for (int i = 0; i < numRules; ++i) {
        delete converserule[i];
    }
    delete [] converserule; // delete converserule
}

