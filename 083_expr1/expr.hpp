#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <sstream>

class Expression {
 public:
  Expression() {}
  virtual ~Expression() {}
  virtual std::string toString() const = 0;
};

class NumExpression : public Expression {
  long num;

 public:
  NumExpression() : num(0) {}
  explicit NumExpression(long n) : num(n) {}
  virtual ~NumExpression() {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << num;
    return ss.str();
  }
};

class PlusExpression : public Expression {
  Expression * lhs_expr;
  Expression * rhs_expr;

 public:
  PlusExpression() : lhs_expr(NULL), rhs_expr(NULL) {}
  PlusExpression(Expression * lhs, Expression * rhs) : lhs_expr(lhs), rhs_expr(rhs) {}
  virtual ~PlusExpression() {
    delete lhs_expr;
    delete rhs_expr;
  }
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs_expr->toString() << " + " << rhs_expr->toString() << ")";
    return ss.str();
  }
};
