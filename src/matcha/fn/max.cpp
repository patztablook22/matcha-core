#include "matcha/fn/max.h"

#include <algorithm>

#include "matcha/iterations/flatiteration.h"

namespace matcha {
namespace fn {

Max::Max(Tin a) {
  inputs_.push_back(a);
  outputs_.push_back(
    new Tensor(a.tensor->dtype(), {})
  );
  linkTensors();
}

void Max::run() {
  FlatIteration<const float, const Tensor> a(*inputs_[0].tensor);
  FlatIteration<float> result(*outputs_[0].tensor);
  *result.begin() = *std::max_element(a.begin(), a.end());
}

}
}