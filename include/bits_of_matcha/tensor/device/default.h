#pragma once

#include "bits_of_matcha/tensor/device/device.h"

namespace matcha {
namespace device {

namespace abstract {
  class Device;
}

struct Default : Device {
  std::shared_ptr<abstract::Computation> add(const Tensor& a, const Tensor& b, Tensor& c) override;
  std::shared_ptr<abstract::Computation> multiply(const Tensor& a, const Tensor& b, Tensor& c) override;
};

}
}