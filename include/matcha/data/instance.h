#pragma once

#include "matcha/tensor.h"

namespace matcha {
namespace data {

struct Instance {
  Instance(Tensor data, Tensor target);
  Instance();

  Tensor data, target;

  operator bool() const;
};

}
}