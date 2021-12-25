#include "matcha/tio.h"

namespace matcha {

TIn::TIn(const Tensor& value)
  : tensor(new Tensor(value)),
    referenced(false)
{}

TIn::TIn(const float scalar)
  : tensor(new Tensor(scalar)),
    referenced(false)
{}

TIn::TIn(Tensor* pointer) 
  : tensor(pointer),
    referenced(true)
{}

TIn::TIn(TOut& tout)
  : tensor(tout.tensor)
{}

TOut::TOut(Tensor* pointer)
  : tensor(pointer),
    referenced(true)
{}

}