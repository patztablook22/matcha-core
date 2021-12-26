#pragma once

#include "matcha/tensor.h"
#include <memory>

namespace matcha {

struct Tin {
  Tin(const Tensor& value);
  Tin(const float scalar);
  Tin(Tensor* pointer);
  Tin(Tout& tout);

  Tensor* tensor;
  bool referenced;

};

struct Tout {
  Tout(const Tensor& value);
  Tout(Tensor* pointer);

  Tensor* tensor;
  bool referenced;
};

}