#ifndef __UNARY_H__
#define __UNARY_H__
#include "expr.h"
#include <string>

class unary : public Expr {
 std::string ope; // store the string of unary operation
 Expr *exp; // store an expression
 public:
 unary(std::string i, Expr *p); // explicit constructor
 int eval() const; // pure virtual
 std::string prettyPrint() const; // pure virtual
 ~unary(); // destructor
};

#endif











