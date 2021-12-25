#include "matcha/fn/max.h"

#include <algorithm>

#include "matcha/iterations/flatiteration.h"

namespace matcha {
namespace fn {

Max::Max(TIn a) {
  inputs_.push_back(a);
  outputs_.push_back(
    new Tensor(a.tensor->dtype(), {})
  );
  linkTensors();
}

void Max::run() {
  ConstFlatIteration<float> a(*inputs_[0].tensor);
  FlatIteration<float> result(*outputs_[0].tensor);
  *result.begin() = *std::max_element(a.begin(), a.end());
}

}
}