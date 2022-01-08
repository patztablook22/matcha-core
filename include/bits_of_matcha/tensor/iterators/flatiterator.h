#pragma once

#include <iterator>

namespace matcha {

class Tensor;

template <class T>
class FlatIterator {
  public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;

    FlatIterator(T* ptr);

    T& operator*();

    FlatIterator operator++();
    FlatIterator operator--();
    FlatIterator operator++(int);
    FlatIterator operator--(int);

    bool operator==(const FlatIterator& other);
    bool operator!=(const FlatIterator& other);

  private:
    T* ptr_;
};

template class FlatIterator<float>;
template class FlatIterator<int  >;

template class FlatIterator<const float>;
template class FlatIterator<const int  >;

}