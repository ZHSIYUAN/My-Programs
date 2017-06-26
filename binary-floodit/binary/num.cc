#include "num.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int num::eval() const{
 return this->val; // eval just return the value of stored number
}

string num::prettyPrint() const{ //have to translate int to string first
 int tempint = this->eval();
 ostringstream ss; // use this method to transfer number to string
 ss << tempint;
 string mystring = ss.str();
 return mystring; // return the string which represents a number
}










