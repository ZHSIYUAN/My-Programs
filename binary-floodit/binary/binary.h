#ifndef __BINARY_H__
#define __BINARY_H__
#include "expr.h"
#include <string>

class binary : public Expr {
 std::string bope; // string of binary operation
 Expr *exp1; // expression to the left
 Expr *exp2; // expression to the right
 public:
 binary(std::string i, Expr *p1, Expr *p2); //explicit constructor
 int eval() const; // pure virtual
 std::string prettyPrint() const; // pure virtual
 ~binary(); // destructor
};

#endif



















