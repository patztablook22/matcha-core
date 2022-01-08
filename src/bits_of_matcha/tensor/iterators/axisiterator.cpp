#include "bits_of_matcha/tensor/iterators/axisiterator.h"
#include "bits_of_matcha/tensor/tensor.h"

#include <cstddef>
#include <numeric>


namespace matcha {

template <class T>
AxisIterator<T>::AxisIterator(const Tensor& tensor, const int axis, T* ptr)
  : tensor_(tensor),
    axis_(axis),
    ptr_(ptr)
{
  stepSize_ = std::accumulate(
    tensor.shape().begin() + axis + 1,
    tensor.shape().end(),
    1, std::multiplies()
  );
}

template <class T>
T& AxisIterator<T>::operator*() {
  return *ptr_;
}

template <class T>
AxisIterator<T> AxisIterator<T>::operator++() {
  ptr_ += stepSize_;
  return *this;
}

template <class T>
AxisIterator<T> AxisIterator<T>::operator--() {
  ptr_ -= stepSize_;
  return *this;
}

template <class T>
AxisIterator<T> AxisIterator<T>::operator++(int) {
  auto temp = *this;
  ptr_ += stepSize_;
  return temp;
}

template <class T>
AxisIterator<T> AxisIterator<T>::operator--(int) {
  auto temp = *this;
  ptr_ -= stepSize_;
  return temp;
}

template <class T>
AxisIterator<T> AxisIterator<T>::operator+(int offset) {
  ptr_ += offset * stepSize_;
  return *this;
}

template <class T>
bool AxisIterator<T>::operator==(const AxisIterator<T>& other) {
  return ptr_ == other.ptr_;
}

template <class T>
bool AxisIterator<T>::operator!=(const AxisIterator<T>& other) {
  return ptr_ != other.ptr_;
}

}