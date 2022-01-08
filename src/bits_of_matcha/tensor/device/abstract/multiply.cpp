#include "bits_of_matcha/tensor/device/abstract/multiply.h"

#include "bits_of_matcha/tensor/tensor.h"

namespace matcha {
namespace device {
namespace abstract {

Multiply::Multiply(const Tensor& a, const Tensor& b, Tensor& c) 
  : a_{a}
  , b_{b}
  , c_{c}
{}

}
}
}