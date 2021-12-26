#pragma once

#include "matcha/iterators/axisiterator.h"

namespace matcha {

template <class T, class Access = Tensor>
class AxisIteration {
  public:
    AxisIteration(Access& tensor, const int axis, void* ptr);

    AxisIterator<T> begin();
    AxisIterator<T> end();
  private:
    Access& tensor_;
    const int axis_;
    T* beginPtr_;
    T* endPtr_;
};

}