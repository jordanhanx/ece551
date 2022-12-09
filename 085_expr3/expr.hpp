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
  virtual long evaluate() const = 0;
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
  virtual long evaluate() const { return num; }
};

class BinaryExpression : public Expression {
  Expression * lhs_expr;
  Expression * rhs_expr;
  char op;

 public:
  BinaryExpression() : lhs_expr(NULL), rhs_expr(NULL), op() {}
  BinaryExpression(Expression * lhs, Expression * rhs, char chr_op) :
      lhs_expr(lhs), rhs_expr(rhs), op(chr_op) {}
  virtual ~BinaryExpression() {
    delete lhs_expr;
    delete rhs_expr;
  }
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs_expr->toString() << " " << op << " " << rhs_expr->toString() << ")";
    return ss.str();
  }
  virtual long evaluate() const {
    switch (op) {
      case '+':
        return lhs_expr->evaluate() + rhs_expr->evaluate();
      case '-':
        return lhs_expr->evaluate() - rhs_expr->evaluate();
      case '*':
        return lhs_expr->evaluate() * rhs_expr->evaluate();
      case '/':
        return lhs_expr->evaluate() / rhs_expr->evaluate();
      default:
        return 0;
    }
  }
};

class PlusExpression : public BinaryExpression {
 public:
  PlusExpression() {}
  PlusExpression(Expression * lhs, Expression * rhs) : BinaryExpression(lhs, rhs, '+') {}
  virtual ~PlusExpression() {}
  virtual std::string toString() const { return BinaryExpression::toString(); }
  virtual long evaluate() const { return BinaryExpression::evaluate(); }
};

class MinusExpression : public BinaryExpression {
 public:
  MinusExpression() {}
  MinusExpression(Expression * lhs, Expression * rhs) : BinaryExpression(lhs, rhs, '-') {}
  virtual ~MinusExpression() {}
  virtual std::string toString() const { return BinaryExpression::toString(); }
  virtual long evaluate() const { return BinaryExpression::evaluate(); }
};

class TimesExpression : public BinaryExpression {
 public:
  TimesExpression() {}
  TimesExpression(Expression * lhs, Expression * rhs) : BinaryExpression(lhs, rhs, '*') {}
  virtual ~TimesExpression() {}
  virtual std::string toString() const { return BinaryExpression::toString(); }
  virtual long evaluate() const { return BinaryExpression::evaluate(); }
};

class DivExpression : public BinaryExpression {
 public:
  DivExpression() {}
  DivExpression(Expression * lhs, Expression * rhs) : BinaryExpression(lhs, rhs, '/') {}
  virtual ~DivExpression() {}
  virtual std::string toString() const { return BinaryExpression::toString(); }
  virtual long evaluate() const { return BinaryExpression::evaluate(); }
};
