#pragma once

#include <vector>
#include <initializer_list>

namespace matcha {

using Indices     = std::vector<int>;
using IndicesInit = std::initializer_list<int>;
using Shape       = std::vector<unsigned>;
using ShapeInit   = std::initializer_list<int>;

struct Range {
  Indices from, size;

  void represent(const Shape& shape);
};


}