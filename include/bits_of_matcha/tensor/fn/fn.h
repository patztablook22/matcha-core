#pragma once

#include "bits_of_matcha/tensor/expr.h"

#include <string>

namespace matcha {

namespace device {
namespace abstract {
  
class Computation;

}
}

namespace fn {

class Fn : public Expr {
  public:

    Fn(ExprWraps ins);
    ~Fn();

    void eval() override;

    void linkOut(Expr* out) override;
    const Tensor& cache(int index = 0) const override;

  private:
    virtual void init() = 0;
    virtual void run() = 0;

  protected:
    std::vector<Tensor*> cache_;


};

}
}