#pragma once

#include "matcha/tensor.h"
#include "matcha/iterators/flatiterator.h"

namespace matcha {

template <class T, class Access = Tensor>
class FlatIteration {
  public:
    FlatIteration(Access& tensor);
    FlatIterator<T> begin();
    FlatIterator<T> end();
  private:
    Access& tensor_;
};

template class FlatIteration<float, Tensor>;
template class FlatIteration<int  , Tensor>;

template class FlatIteration<const float, const Tensor>;
template class FlatIteration<const int  , const Tensor>;

};