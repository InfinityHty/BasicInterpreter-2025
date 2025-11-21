// TODO: Imply interfaces declared in the Program.hpp.
#include "Program.hpp"
#include <iostream>
#include "utils/Error.hpp"
Program::Program() {
}
void Program::addStmt(int line, Statement* stmt) {
  recorder_.add(line,stmt);
}
void Program::removeStmt(int line) {
  recorder_.remove(line);
}
void Program::run() {
  programEnd_ = false;
  programCounter_ = recorder_.nextLine(0);
  while (programCounter_ != -1 && programEnd_ == false) {
    int tmp = programCounter_;
    const Statement* stmt = recorder_.get(programCounter_);
    //std::cerr << programCounter_ << " " << stmt->text() << std::endl;
    stmt->execute(vars_,*this);
    if (programCounter_ == tmp) programCounter_ = recorder_.nextLine(programCounter_);
    else if (!recorder_.hasLine(programCounter_)) {
      throw BasicError("LINE NUMBER ERROR");
    }
  }
}
void Program::list() const {
  recorder_.printLines();
}
void Program::clear() {
  recorder_.clear();
  vars_.clear();
}
//执行不带行号的语句
void Program::execute(Statement* stmt) {
  stmt->execute(vars_,*this);
}

int Program::getPC() const noexcept {
  return programCounter_;
}
void Program::changePC(int line) {
  programCounter_ = line;
}
void Program::programEnd() {
  programEnd_ = true;
  //resetAfterRun();
}
void Program::resetAfterRun() noexcept {
  clear();
}