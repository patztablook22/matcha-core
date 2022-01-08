#include "bits_of_matcha/tensor/device/cpu.h"

#include "bits_of_matcha/tensor/tensor.h"
#include "bits_of_matcha/tensor/device/cpu/add.h"
#include "bits_of_matcha/tensor/device/cpu/multiply.h"

namespace matcha {
namespace device {

std::shared_ptr<abstract::Computation> Cpu::add(const Tensor& a, const Tensor& b, Tensor& c) {
  return std::make_shared<cpu::Add>(a, b, c);
}

std::shared_ptr<abstract::Computation> Cpu::multiply(const Tensor& a, const Tensor& b, Tensor& c) {
  return std::make_shared<cpu::Multiply>(a, b, c);
}

}
}