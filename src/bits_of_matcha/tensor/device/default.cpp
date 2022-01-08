#include "bits_of_matcha/tensor/device/default.h"

#include "bits_of_matcha/tensor/tensor.h"
#include "bits_of_matcha/tensor/device/cpu.h"
#include "bits_of_matcha/tensor/device/threadpool.h"

namespace matcha {
namespace device {

std::shared_ptr<abstract::Computation> Default::add(const Tensor& a, const Tensor& b, Tensor& c) {
  if (a.size() < 1e6) 
    return Cpu().add(a, b, c);
  else
    return ThreadPool().add(a, b, c);
}

std::shared_ptr<abstract::Computation> Default::multiply(const Tensor& a, const Tensor& b, Tensor& c) {
  if (a.size() < 1e6)
    return Cpu().add(a, b, c);
  else
    return ThreadPool().multiply(a, b, c);
}

}
}