#pragma once

#include "bits_of_matcha/tensor/device/cpu.h"

namespace matcha {
namespace device {

namespace abstract {
  class Add;
}

struct ThreadPool : Cpu {
  public:
    ThreadPool(int threads = -1);

    std::shared_ptr<abstract::Computation> add(const Tensor& a, const Tensor& b, Tensor& c) override;
    std::shared_ptr<abstract::Computation> multiply(const Tensor& a, const Tensor& b, Tensor& c) override;

  private:
    int threads_;
};

}
}