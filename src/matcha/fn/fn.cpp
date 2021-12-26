#include "matcha/fn/fn.h"
#include <iostream>

#include <cassert>

namespace matcha {
namespace fn {

Fn::Fn()
  : updated_(true)
{}

bool Fn::updated() const {
  return updated_;
}

void Fn::update() {
  // std::cout << "updating fn " << mark << std::endl;
  for (auto& tout: outputs_) tout.tensor->update();
  updated_ = true;
}

void Fn::redirect(unsigned index, Tensor* tensor) {
  const Shape& oldShape = outputs_[index].tensor->shape();
  const Shape& newShape = tensor->shape();
  assert(std::equal(newShape.begin(), newShape.end(), oldShape.begin()));
  outputs_[index].tensor = tensor;
}

void Fn::eval() {
  if (!updated()) return;
  for (auto& tin: inputs_) tin.tensor->eval();
  updated_ = false;
  run();
}

unsigned Fn::outputs() const {
  return outputs_.size();
}

Tout& Fn::output(unsigned index) {
  return outputs_[index];
}

void Fn::linkTensors() {
  for (auto& tin: inputs_) tin.tensor->to_ = this;
  for (auto& tout: outputs_) {
    tout.tensor->from_ = this;
    tout.tensor->update();
  }
}

}
}