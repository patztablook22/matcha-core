#include "matcha/fn/sum.h"

#include <numeric>

#include "matcha/iterations/flatiteration.h"

namespace matcha {
namespace fn {

Sum::Sum(TIn a) {
  inputs_.push_back(a);
  outputs_.push_back(
    new Tensor(a.tensor->dtype(), {})
  );
  linkTensors();
}

void Sum::run() {
  ConstFlatIteration<float> a(*inputs_[0].tensor);
  FlatIteration<float> result(*outputs_[0].tensor);
  *result.begin() = std::accumulate(a.begin(), a.end(), .0);
}

}
}