// TODO: Imply interfaces declared in the Recorder.hpp.
#include "Recorder.hpp"
#include<iostream>
Recorder::~Recorder() {
  sentences.clear();
}
void Recorder::add(int line,Statement* state) {
  sentences[line] = state;
}
void Recorder::remove(int line) {
  if (hasLine(line))
    sentences.erase(line);
}
//map的中[]返回类型不是const但用迭代器可以返回const
const Statement* Recorder::get(int line) const noexcept {
  if (hasLine(line)) {
    auto it = sentences.find(line);
    return it->second;
  }
  else return nullptr;
}
bool Recorder::hasLine(int line) const noexcept {
  if (sentences.find(line) != sentences.end()) return true;
  else return false;
}
void Recorder::clear() noexcept {
  sentences.clear();
}
void Recorder::printLines() const {
  for (auto it = sentences.begin(); it != sentences.end(); it++) {
    std::cout << (it->second) << std::endl;
  }
}
int Recorder::nextLine(int line) const noexcept {
  auto it = sentences.upper_bound(line);
  if (it == sentences.end()) return -1;
  else return it->first;
}