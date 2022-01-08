#pragma once

#include "bits_of_matcha/tensor/device/abstract/multiply.h"

namespace matcha {
namespace device {
namespace cpu {

class Multiply : public abstract::Multiply {
  public:
    Multiply(const Tensor& a, const Tensor& b, Tensor& c);
    void init() override;
    void run() override;
  
  private:
    int threads_;
};


}
}
}