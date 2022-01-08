#include "bits_of_matcha/tensor/device/abstract/add.h"

#include "bits_of_matcha/tensor/tensor.h"

namespace matcha {
namespace device {
namespace abstract {

Add::Add(const Tensor& a, const Tensor& b, Tensor& c) 
  : a_{a}
  , b_{b}
  , c_{c}
{}

}
}
}