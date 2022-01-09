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
{
  begA = &a_.at<float>(0);
  endA = &a_.at<float>(0) + a_.size();
  begB = &b_.at<float>(0);
  begC = &c_.at<float>(0);
}

void Add::init() {
}

void Add::run() {
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