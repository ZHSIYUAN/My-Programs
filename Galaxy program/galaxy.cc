//
//  galaxy.cpp
//  wlp4scan.cc
//
//  Created by Siyuan Guo on 2016-11-03.
//  Copyright © 2016 Siyuan Guo. All rights reserved.
//
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

//Skip the grammar part of the input.
void skipLine(istream &in) {
    string s;
    getline(in, s);
}

void skipGrammar(istream &in) {
    int i, numTerm, numNonTerm, numRules;
    
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
    skipLine(in);
    
    // read the number of rules and move to the next line
    in >> numRules;
    skipLine(in);
    
    // skip the lines containing the production rules
    for (i = 0; i < numRules; i++) {
        skipLine(in);
    }
}




string trim(const string &str) {
    size_t begin = str.find_first_not_of(" \t\n");
    if (begin == string::npos) return "";
    
    size_t end = str.find_last_not_of(" \t\n");
    
    return str.substr(begin, end - begin + 1);
}

/* Prints the derivation with whitespace trimmed.
void printDerivation(istream &in, ostream &out) {
    string line;
    
    while (getline(in, line)) {
        out << trim(line) << '\n';
    }
}
 */

string firstdriv = "expr term";
string seconddriv = "expr expr - term";
string thirddriv = "term id";
string fourthdriv = "term (expr)";

int myrecursion(istream &in) {
    string line;
    getline(in ,line);
    string myline = line;
    myline = trim(myline);
    if (myline == firstdriv) {
        return myrecursion(in);
    } else if (myline == seconddriv) {
        return myrecursion(in) - myrecursion(in);
    } else if (myline == thirddriv) {
        return 42; // the expr will finally reach the end of
    } else {  // fourthdriv
        return myrecursion(in);
    }
}

// Reads a .cfg file and prints the left-canonical
// derivation without leading or trailing spaces.
int main() {
    skipGrammar(std::cin);
    skipLine(std::cin);
    int i = myrecursion(std::cin);
    cout << i << endl;
    //printDerivation(std::cin, std::cout);
}

