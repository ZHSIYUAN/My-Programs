#include "binary.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

// explicit constructor
binary::binary(string i, Expr *p1, Expr *p2) : bope(i), exp1(p1), exp2(p2) {}

int binary::eval() const{
 string temp = this->bope;
 if (temp == "+") { // determine which operation is it
  return exp1->eval() + exp2->eval(); // return value according to operator
 } else if (temp == "-") {
  return exp1->eval() - exp2->eval();
 } else if (temp == "*") {
  return exp1->eval() * exp2->eval();
 } else {
  return exp1->eval() / exp2->eval();
 }
}

string binary::prettyPrint() const{
 string newstring = "(" + exp1->prettyPrint() + " "
              + this->bope + " " + exp2->prettyPrint() + ")"; // add operator between two expression, add parentheses on both sides
 return newstring;
}


binary::~binary() {
 delete exp1; // delete these two expressions
 delete exp2;
}


















