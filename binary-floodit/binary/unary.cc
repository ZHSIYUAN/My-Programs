#include "unary.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

unary::unary(string i, Expr *p) : ope(i), exp(p) {} // explicit constructor

int unary::eval() const{
 if (ope == "NEG") { // determine whether its NEG or ABS
  return -(exp->eval()); // return value according to the operation
 } else { // apply absolute operation
  int temp = exp->eval();
  if (temp < 0) { // for negative number
   return -(exp->eval());
  } else {
   return exp->eval(); // for positive number
  }
 } 
}

string unary::prettyPrint() const{
 if (ope == "ABS") { 
  string newstring = "|" + exp->prettyPrint() + "|"; // add | | to both sides of the original expression
  return newstring;
 } else {
  string newstring = "-" + exp->prettyPrint(); // add - in front of the original expression
  return newstring;
 } 
}

unary::~unary() {
 delete exp; // delete the expression it contians
}

