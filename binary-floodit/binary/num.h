#ifndef __NUM_H__
#define __NUM_H__
#include "expr.h"

class num : public Expr {
 int val; // store the value of read in numbers
 public:
 num(int k) : val(k) {} //my explicit constructor
 int eval() const; // has to match the routine in Expr (pure virtual)
 std::string prettyPrint() const; // has to match the routine in Expr (pure virtual)
};

#endif


