#pragma once

#include <iterator>

#include "matcha/AbstractTensor.h"
#include "matcha/range.h"


namespace matcha {

template <class>
class AbstractTensor;

template <class T>
struct AbstractTensor<T>::LinearIterator {
  public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;

    LinearIterator(T* ptr);
    virtual LinearIterator operator++();
    virtual LinearIterator operator--();
    LinearIterator operator++(int);
    LinearIterator operator--(int);
    virtual T& operator*();
    bool operator==(const LinearIterator& other);
    bool operator!=(const LinearIterator& other);

    MultidimensionalIterator& operator=(const MultidimensionalIterator& other);

  protected:
    LinearIterator();
    T* ptr;
};

template class AbstractTensor<double>::LinearIterator;
template class AbstractTensor<int   >::LinearIterator;

}