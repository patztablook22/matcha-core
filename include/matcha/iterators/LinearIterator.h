#pragma once

#include "matcha/AbstractTensor.h"
#include "matcha/range.h"

namespace matcha {

template <class>
class AbstractTensor;

template <class T>
class AbstractTensor<T>::LinearIterator {
  public:
    LinearIterator(T* ptr);
    virtual LinearIterator operator++();
    virtual LinearIterator operator--();
    LinearIterator operator++(int);
    LinearIterator operator--(int);
    virtual T& operator*();
    bool operator==(const LinearIterator& other);
    bool operator!=(const LinearIterator& other);
  protected:
    LinearIterator();
    T* ptr;
};

template class AbstractTensor<double>::LinearIterator;
template class AbstractTensor<int   >::LinearIterator;

}