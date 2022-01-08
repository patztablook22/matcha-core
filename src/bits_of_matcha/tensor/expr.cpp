#include "bits_of_matcha/tensor/expr.h"
#include "bits_of_matcha/tensor/tensor.h"

namespace matcha {

Expr::Expr(ExprWraps ins)
  : required_{true}
  , ins_{ins}
{
  // cout << ins_.size() << endl;
  // for (auto& in: ins_) in->outs_.push_back(this);
}

Expr::Expr(const Expr& other)
  : required_{other.required_}
  , ins_{other.ins_}
  , outs_{other.outs_}
{
  // std::cout << "rvalue constructor called" << endl;
}

Expr::~Expr() {
}

void Expr::linkOut(Expr* out) {
  outs_.push_back(out);
  for(auto& in: ins_) in->linkOut(this);
  if (required_) {
    for (auto& out: outs_) out->require();
  }
}

void Expr::unlinkOut(Expr* out) {
  // outs_.erase(out);
  auto it = std::find_if(
    outs_.begin(), outs_.end(),
    [&request = out] (auto out) {
      return &*out == request;
    }
  );
  outs_.erase(it);

  for (auto& in: ins_) in->unlinkOut(this);
}

void Expr::require() {
  // cout << "setting behind " << this << endl;
  // cout << "behind: " << (required_ ? "true" : "false") << endl;
  // cout << "size: " << outs_.size() << endl;
  // if (outs_.size() > 0)
  //   cout << "outs_[0] = " << &*outs_[0] << endl;
  if (required_) return;
  required_ = true;

  for(auto& out: outs_) out->require();
}

bool Expr::required() const {
  return required_;
}

}