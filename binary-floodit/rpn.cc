#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <typeinfo> // fuck this
#include "expr.h"
#include "num.h"
#include "unary.h"
#include "binary.h"
using namespace std;


const int MAX_EXPRS = 10;

int main () {
  string s;
  Expr *stack[MAX_EXPRS];
  int index = -1;
  while (cin >> s) {
    istringstream ss(s);
    int n;
    if (ss >> n) { // determine whether the thing is a number
     ++index;
     if (index > 9) { // more than 10 expression in the stack, overflow!
      cerr << "Stack overflow" << endl; // error message
      exit(1); // terminate the program
     }
     Expr *mynew = new num(n); // initialize new expression
     stack[index] = mynew; // pass its address into stack
    }
    else {       
      if (s == "NEG") {
       Expr *mynew = new unary(s, stack[index]); // new expression
       stack[index] = mynew; // pass address to stack
      }
      else if (s == "ABS") {
       Expr *mynew = new unary(s, stack[index]); // new expression
       stack[index] = mynew; // pass address to stack
      }
      else if (s == "+") {
       Expr *mynew = new binary(s, stack[index - 1], stack[index]); // new expression
       stack[index - 1] = mynew; // pass value to stack
       index = index - 1; // reduce the stack size because its binary
      }
      else if (s == "-") {
       Expr *mynew = new binary(s, stack[index - 1], stack[index]);
       stack[index - 1] = mynew; // same as before
       index = index - 1;
      }
      else if (s == "*") {
       Expr *mynew= new binary(s, stack[index - 1], stack[index]);
       stack[index - 1] = mynew; // same as before
       index = index - 1;
      }
      else if (s == "/") {
       Expr *mynew = new binary(s, stack[index - 1], stack[index]);
       stack[index - 1] = mynew; // same as before
       index = index - 1;
      }
    }
  }
  cout << stack[0]->prettyPrint() << endl; // output the expression
  cout << "= " << stack[0]->eval() << endl; // output the result
  delete stack[0]; // delete the only expression left
}



