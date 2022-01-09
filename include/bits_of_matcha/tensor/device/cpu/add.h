#pragma once

#include "bits_of_matcha/tensor/device/abstract/add.h"

namespace matcha {
namespace device {
namespace cpu {

class Add : public abstract::Add {
  public:
    Add(const Tensor& a, const Tensor& b, Tensor& c);
    void init() override;
    void run() override;
  
  private:
    int threads_;

    const float* begA;
    const float* endA;
    const float* begB;
    float* begC;
};


}
}
}