#include "VarState.hpp"

#include <algorithm>
#include <map>

#include "utils/Error.hpp"

void VarState::setValue(const std::string& name, int value) {
  values_[layer][name] = value;
}

int VarState::getValue(const std::string& name) const {
  int now_layer = layer;
  //bool found = false;
  while (now_layer >= 0) {
    auto it = values_[now_layer].find(name);
    if (it == values_[now_layer].end()) {
      now_layer--;
    }
    else {
      return it->second;
    }
  }
  throw BasicError("VARIABLE NOT DEFINED");
}
void VarState::indent() {
  layer++;
  values_.resize(layer + 1);
}
void VarState::dedent() {
  if (layer == 0) {
    throw BasicError("SCOPE UNDERFLOW");
  }
  else {
    values_.pop_back();
    layer--;
  }
}
void VarState::clear() { values_.clear(); }
