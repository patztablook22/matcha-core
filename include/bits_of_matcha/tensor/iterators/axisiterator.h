#pragma once

#include <iterator>

namespace matcha {

class Tensor;

template <class T>
class AxisIterator {
  public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;

    AxisIterator(const Tensor& tensor, const int axis, T* ptr);

    T& operator*();

    AxisIterator operator++();
    AxisIterator operator--();
    AxisIterator operator++(int);
    AxisIterator operator--(int);

    AxisIterator operator+(int offset);

    bool operator==(const AxisIterator& other);
    bool operator!=(const AxisIterator& other);

  private:
    const Tensor& tensor_;
    const int axis_;
    size_t stepSize_;
    T* ptr_;
};

template class AxisIterator<float>;
template class AxisIterator<int  >;

template class AxisIterator<const float>;
template class AxisIterator<const int  >;

}