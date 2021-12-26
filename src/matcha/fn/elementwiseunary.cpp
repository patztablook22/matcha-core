#include "matcha/fn/elementwiseunary.h"
#include <assert.h>
#include "matcha/iterations/flatiteration.h"

#include <algorithm>
#include <numeric>
#include <execution>

#include <iostream>

namespace matcha {
namespace fn {

ElementWiseUnary::ElementWiseUnary(Tin a) {
  inputs_.push_back(a);
  outputs_.push_back(
    new Tensor(a.tensor->dtype(), a.tensor->shape())
  );
  linkTensors();
}

void ElementWiseUnary::run() {
  FlatIteration<const float, const Tensor> a(*inputs_[0].tensor);
  FlatIteration<float> result(*outputs_[0].tensor);

  std::transform(a.begin(), a.end(), result.begin(), [this](float a) {return this->runElement(a);});
}


}
}