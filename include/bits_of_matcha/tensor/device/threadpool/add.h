#pragma once

#include "bits_of_matcha/tensor/device/abstract/add.h"

namespace matcha {
namespace device {

struct ThreadPool;

namespace threadpool {

class Add : public abstract::Add {
  public:
    Add(const Tensor& a, const Tensor& b, Tensor& c);
    void init() override;
    void run() override;

  private:
    int threads_;

    friend struct device::ThreadPool;
};


}
}
}