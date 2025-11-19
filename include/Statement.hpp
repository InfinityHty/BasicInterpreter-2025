#pragma once

#include <memory>
#include <string>

#include "Expression.hpp"

class Program;
class VarState;

class Statement {
 public:
  explicit Statement(std::string source);
  virtual ~Statement() = default;

  virtual void execute(VarState& state, Program& program) const = 0;

  const std::string& text() const noexcept;

 private:
  std::string source_;
};

// TODO: Other statement types derived from Statement, e.g., GOTOStatement,
// LetStatement, etc.
class LetStatement : public Statement {
private:
  Expression* expression;
public:
  void execute(VarState& state, Program& program) const override;
  LetStatement(std::string source,Expression* expr) : Statement(source) {
    expression = expr;
  }
};
class PrintStatement : public Statement {
private:
  Expression* expression;
public:
  void execute(VarState& state, Program& program) const override;
  PrintStatement(Expression* expr) : Statement("") {
    expression = expr;
  }
};
class InputStatement : public Statement {
public:
  void execute(VarState& state, Program& program) const override;
  InputStatement(std::string source) : Statement(source) {}
};
class GotoStatement : public Statement {
private:
  int line_number;
public:
  void execute(VarState& state, Program& program) const override;
  GotoStatement(int line) : Statement("") {
    line_number = line;
  }
};
class IfStatement : public Statement {
private:
  Expression* left;
  Expression* right;
  char op;
  int target;
public:
  void execute(VarState& state, Program& program) const override;
  IfStatement(Expression* l,char op,Expression* r,int target) : Statement("") {
    left = l,right = r;
    this->op = op;
    this->target = target;
  }
};
class RemStatement : public Statement {
public:
  void execute(VarState& state, Program& program) const override;
  RemStatement() : Statement("") {}
};
class EndStatement : public Statement {
public:
  void execute(VarState& state, Program& program) const override;
  EndStatement() : Statement("") {}
};