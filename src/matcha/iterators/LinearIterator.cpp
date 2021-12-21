#include "matcha/iterators/LinearIterator.h"

namespace matcha {

template <class T>
AbstractTensor<T>::LinearIterator::LinearIterator(T* ptr)
  :ptr(ptr)
{}

template <class T>
AbstractTensor<T>::LinearIterator::LinearIterator()
  :ptr(nullptr)
{}

template <class T>
AbstractTensor<T>::LinearIterator AbstractTensor<T>::LinearIterator::operator++() {
  ptr++;
  return *this;
}

template <class T>
AbstractTensor<T>::LinearIterator AbstractTensor<T>::LinearIterator::operator++(int) {
  auto temp = *this;
  ptr++;
  return temp;
}

template <class T>
AbstractTensor<T>::LinearIterator AbstractTensor<T>::LinearIterator::operator--() {
  ptr--;
  return *this;
}

template <class T>
AbstractTensor<T>::LinearIterator AbstractTensor<T>::LinearIterator::operator--(int) {
  auto temp = *this;
  ptr--;
  return temp;
}

template <class T>
bool AbstractTensor<T>::LinearIterator::operator==(const LinearIterator& other) {
  return ptr == other.ptr;
}

template <class T>
bool AbstractTensor<T>::LinearIterator::operator!=(const LinearIterator& other) {
  return ptr != other.ptr;
}

template <class T>
T& AbstractTensor<T>::LinearIterator::operator*() {
  return *ptr;
}

}