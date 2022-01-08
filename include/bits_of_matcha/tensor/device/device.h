#pragma once

#include <memory>
#include "bits_of_matcha/tensor/device/abstract/computation.h"

namespace matcha {

class Tensor;

namespace device {

namespace abstract {
  class Add;
}

struct Device {
  virtual std::shared_ptr<abstract::Computation> add(const Tensor& a, const Tensor& b, Tensor& c) = 0;
  virtual std::shared_ptr<abstract::Computation> multiply(const Tensor& a, const Tensor& b, Tensor& c) = 0;
};

}
}