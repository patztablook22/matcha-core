#include "matcha/data/instance.h"

#include "matcha/tensor.h"

namespace matcha {
namespace data {

Instance::Instance(Tensor data, Tensor target)
  : data(data),
    target(target)
{}

Instance::Instance()
  : data(),
    target()
{}

Instance::operator bool() const {
  return !(data.null() && target.null());
}

}
}