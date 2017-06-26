#ifndef __EXPR_H__
#define __EXPR_H__
#include <string>

class Expr { // the value of current expr
 public:
  virtual int eval() const = 0;
  virtual std::string prettyPrint() const = 0;
  virtual ~Expr() {};
};


#endif


