#include "bits_of_matcha/tensor/device/cpu/add.h"

#include "bits_of_matcha/tensor/tensor.h"

#include <algorithm>
#include <numeric>
#include <execution>

namespace matcha {
namespace device {
namespace cpu {

Add::Add(const Tensor& a, const Tensor& b, Tensor& c) 
  : abstract::Add(a, b, c)
{}

void Add::init() {
}

void Add::run() {
  const float* begA = &a_.at<float>(0);
  const float* endA = &a_.at<float>(0) + a_.size();
  const float* begB = &b_.at<float>(0);
  float* begC = &c_.at<float>(0);

  std::transform(
    begA, endA,
    begB,
    begC,
    std::plus()
  );
}

}
}
}