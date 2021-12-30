#include "matcha/fn/accuracy.h"

#include <numeric>
#include <cassert>

#include "matcha/iterations/flatiteration.h"

namespace matcha {
namespace fn {

Accuracy::Accuracy(Tin guess, Tin truth) {
  assert(guess.tensor->rank() == truth.tensor->rank());
  assert(guess.tensor->rank() == 1);
  assert(guess.tensor->shape()[0] == truth.tensor->shape()[0]);
  inputs_.push_back(guess);
  inputs_.push_back(truth);
  outputs_.push_back(
    new Tensor(Dtype::Float, {})
  );
  linkTensors();
}

void Accuracy::run() {
  FlatIteration<const float, const Tensor> guess(*inputs_[0].tensor);
  FlatIteration<const float, const Tensor> truth(*inputs_[1].tensor);
  FlatIteration<float> result(*outputs_[0].tensor);
  double correct = 0;
  size_t total   = inputs_[0].tensor->size();

  auto guessIter = guess.begin();
  for (auto t: truth) {
    if (t == *guessIter) correct++;
    guessIter++;
  }

  *result.begin() = correct / total;
}

}
}