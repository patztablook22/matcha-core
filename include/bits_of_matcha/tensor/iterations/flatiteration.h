#pragma once

#include "bits_of_matcha/tensor/iterators/flatiterator.h"

namespace matcha {

class Tensor;

template <class T>
class FlatIterator;

template <class T, class Access>
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