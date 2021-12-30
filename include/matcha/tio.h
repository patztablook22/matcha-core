#pragma once

#include <memory>

namespace matcha {

class Tensor;
namespace fn {
  class Fn;
}

struct Tin;
struct Tout;

struct Tin {
  Tin(const Tensor& value);
  Tin(const float scalar);
  Tin(Tensor* pointer);
  Tin(Tout& tout);
  ~Tin();

  Tensor* tensor;
  fn::Fn* fn;
  bool referenced;

};

struct Tout {
  Tout(const Tensor& value);
  Tout(Tensor* pointer);
  ~Tout();

  Tensor* tensor;
  fn::Fn* fn;
  bool referenced;
};

}