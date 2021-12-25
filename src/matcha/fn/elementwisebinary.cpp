#include "matcha/fn/elementwisebinary.h"
#include <assert.h>
#include "matcha/iterations/flatiteration.h"

#include <algorithm>
#include <numeric>
#include <execution>

#include <iostream>

namespace matcha {
namespace fn {

ElementWiseBinary::ElementWiseBinary(TIn a, TIn b) {
  if (a.tensor->scalar()) std::swap(a, b);
  assert(a.tensor->shape() == b.tensor->shape() || b.tensor->scalar());
  inputs_.push_back(a);
  inputs_.push_back(b);
  outputs_.push_back(
    new Tensor(a.tensor->dtype(), a.tensor->shape())
  );
  linkTensors();
}

void ElementWiseBinary::run() {
  ConstFlatIteration<float> a(*inputs_[0].tensor);
  ConstFlatIteration<float> b(*inputs_[1].tensor);
  FlatIteration<float> result(*outputs_[0].tensor);

  if (inputs_[1].tensor->scalar()) {
    float bElem = *b.begin();
    std::transform(
      a.begin(), a.end(),
      result.begin(), 
      [this, &bElem](float aElem) {return this->runElement(aElem, bElem);}
    );
  } else {
    std::transform(
      a.begin(), a.end(), b.begin(),
      result.begin(), 
      [this](float aElem, float bElem) {return this->runElement(aElem, bElem);}
    );
  }
}


}
}