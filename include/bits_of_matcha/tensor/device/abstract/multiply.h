#pragma once

#include "bits_of_matcha/tensor/device/abstract/computation.h"

namespace matcha {

class Tensor;

namespace device {
namespace abstract {

class Multiply : public Computation {
  public:
    Multiply(const Tensor& a, const Tensor& b, Tensor& c);
  
  protected:
    const Tensor& a_;
    const Tensor& b_;
    Tensor& c_;
};

}
}
}