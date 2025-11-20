#include "Statement.hpp"

#include <iostream>
#include <limits>
#include <sstream>
#include <utility>

#include "Program.hpp"
#include "VarState.hpp"
#include "utils/Error.hpp"

Statement::Statement(std::string source) : source_(std::move(source)) {}

const std::string& Statement::text() const noexcept { return source_; }

// TODO: Imply interfaces declared in the Statement.hpp.
void LetStatement::execute(VarState& state, Program& program) const{
  state.setValue(varName,expression->evaluate(state));
}
void PrintStatement::execute(VarState& state, Program& program) const {
  std::cout << expression->evaluate(state) << std::endl;
}
void InputStatement::execute(VarState& state, Program& program) const {
  std::cout << "?";
  int input_value;
  std::cin >> input_value;
  state.setValue(varName,input_value);
}
void GotoStatement::execute(VarState& state, Program& program) const {
  program.changePC(line_number);
}
void IfStatement::execute(VarState& state, Program& program) const {
  bool flag = false;
  switch (op) {
    case '>':
      if (left->evaluate(state) > right->evaluate(state)) flag = true;
      break;
    case '<':
      if (left->evaluate(state) < right->evaluate(state)) flag = true;
      break;
    case '=':
      if (left->evaluate(state) == right->evaluate(state)) flag = true;
      break;
    default:;
  }
  if (flag) program.changePC(target);

}
void RemStatement::execute(VarState& state, Program& program) const {
}
void EndStatement::execute(VarState& state, Program& program) const {
  program.programEnd();
}