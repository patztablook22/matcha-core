#pragma once

#include "matcha/tensor.h"
#include "matcha/iterators/flatiterator.h"

namespace matcha {

template <class T>
class FlatIteration {
  public:
    FlatIteration(Tensor& tensor);
    FlatIterator<T> begin();
    FlatIterator<T> end();
  private:
    Tensor* tensor_;
};

template class FlatIteration<float>;
template class FlatIteration<int  >;

template <class T>
class ConstFlatIteration {
  public:
    ConstFlatIteration(const Tensor& tensor);
    FlatIterator<const T> begin();
    FlatIterator<const T> end();
  private:
    const Tensor* tensor_;
};

template class ConstFlatIteration<float>;
template class ConstFlatIteration<int  >;

};