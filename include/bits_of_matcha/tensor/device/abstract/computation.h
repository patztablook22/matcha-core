#pragma once

#include "bits_of_matcha/tensor/tensor.h"

namespace matcha {

class Tensor;

namespace device {
namespace abstract {

class Computation {
  public:
    virtual void init() = 0;
    virtual void run() = 0;
};

}
}
}