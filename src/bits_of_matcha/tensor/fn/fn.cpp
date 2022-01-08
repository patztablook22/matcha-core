#include "bits_of_matcha/tensor/fn/fn.h"
#include "bits_of_matcha/tensor/tensor.h"

namespace matcha {
namespace fn {

Fn::Fn(ExprWraps ins)
  : Expr({ins})
{}

Fn::~Fn() {
  for (auto& cache: cache_) delete cache;
}

void Fn::eval() {
  if (!required_) return;
  required_ = false;

  for(auto& in: ins_) in->eval();
  run();

  // cout << "evaluating fn " << this << endl;

}

void Fn::linkOut(Expr* out) {
  outs_.push_back(out);
  for(auto& in: ins_) in->linkOut(this);
  init();
  if (required_) {
    for (auto& out: outs_) out->require();
  }
  // cout << "linking out fn " << this << " to " << &*out << endl;
}

const Tensor& Fn::cache(int index) const {
  return *cache_[index];
}


}
}