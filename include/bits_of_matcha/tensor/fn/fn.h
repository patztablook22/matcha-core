#pragma once

#include "bits_of_matcha/tensor/expr.h"

#include <string>

namespace matcha {

namespace device {
  class Device;

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

    virtual void use(device::Device& device) override;

  private:
    virtual void init() = 0;
    virtual void run() = 0;

  protected:
    std::vector<Tensor*> cache_;

    device::Device* device_;


};

}
}