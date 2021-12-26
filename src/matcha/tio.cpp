#include "matcha/tio.h"

namespace matcha {

Tin::Tin(const Tensor& value)
  : tensor(new Tensor(value)),
    referenced(false)
{}

Tin::Tin(const float scalar)
  : tensor(new Tensor(scalar)),
    referenced(false)
{}

Tin::Tin(Tensor* pointer) 
  : tensor(pointer),
    referenced(true)
{}

Tin::Tin(Tout& tout)
  : tensor(tout.tensor)
{}

Tout::Tout(Tensor* pointer)
  : tensor(pointer),
    referenced(true)
{}

}