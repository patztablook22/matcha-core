#pragma once

#include "matcha/tensor.h"
#include <memory>

namespace matcha {

struct TIn {
  TIn(const Tensor& value);
  TIn(const float scalar);
  TIn(Tensor* pointer);
  TIn(TOut& tout);

  Tensor* tensor;
  bool referenced;

};

struct TOut {
  TOut(const Tensor& value);
  TOut(Tensor* pointer);

  Tensor* tensor;
  bool referenced;
};


}