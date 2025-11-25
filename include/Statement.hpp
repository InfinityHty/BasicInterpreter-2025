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
  std::string varName;
public:
  void execute(VarState& state, Program& program) const override;
  LetStatement(std::string varname,Expression* expr,std::string originLine) : Statement(originLine) {
    expression = expr;
    this->varName = varname;
  }
  ~LetStatement() override {
    delete expression;
  };
};
class PrintStatement : public Statement {
private:
  Expression* expression;
public:
  void execute(VarState& state, Program& program) const override;
  PrintStatement(Expression* expr,std::string originLine) : Statement(originLine) {
    expression = expr;
  }
  ~PrintStatement() override {
    delete expression;
  }
};
class InputStatement : public Statement {
private:
  std::string varName;
public:
  void execute(VarState& state, Program& program) const override;
  InputStatement(std::string varname,std::string originLine) : Statement(originLine) {
    this->varName = varname;
  }
  ~InputStatement() override = default;
};
class GotoStatement : public Statement {
private:
  int line_number;
public:
  void execute(VarState& state, Program& program) const override;
  GotoStatement(int line,std::string originLine) : Statement(originLine) {
    line_number = line;
  }
  ~GotoStatement() override = default;
};
class IfStatement : public Statement {
private:
  Expression* left;
  Expression* right;
  char op;
  int target;
public:
  void execute(VarState& state, Program& program) const override;
  IfStatement(Expression* l,char op,Expression* r,int target,std::string originLine) : Statement(originLine) {
    left = l,right = r;
    this->op = op;
    this->target = target;
  }
  ~IfStatement() override {
    delete left;
    delete right;
  }
};
class RemStatement : public Statement {
public:
  void execute(VarState& state, Program& program) const override;
  RemStatement(std::string originLine) : Statement(originLine) {}
  ~RemStatement() override = default;
};
class EndStatement : public Statement {
public:
  void execute(VarState& state, Program& program) const override;
  EndStatement(std::string originLine) : Statement(originLine) {}
  ~EndStatement() override = default;
};
class IndentStatement : public Statement {
public:
  void execute(VarState& state, Program& program) const override;
  IndentStatement(std::string originLine) : Statement(originLine) {}
  ~IndentStatement() override = default;
};
class DedentStatement : public Statement {
  public:
  void execute(VarState& state, Program& program) const override;
  DedentStatement(std::string originLine) : Statement(originLine) {}
  ~DedentStatement() override = default;
};