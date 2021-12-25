#include "matcha/iterators/flatiterator.h"

namespace matcha {

template <class T>
FlatIterator<T>::FlatIterator(T* ptr)
  : ptr_(ptr)
{}

template <class T>
T& FlatIterator<T>::operator*() {
  return *ptr_;
}

template <class T>
FlatIterator<T> FlatIterator<T>::operator++() {
  ptr_++;
  return *this;
}

template <class T>
FlatIterator<T> FlatIterator<T>::operator--() {
  ptr_--;
  return *this;
}

template <class T>
FlatIterator<T> FlatIterator<T>::operator++(int) {
  FlatIterator temp = *this;
  ptr_++;
  return temp;
}

template <class T>
FlatIterator<T> FlatIterator<T>::operator--(int) {
  FlatIterator temp = *this;
  ptr_--;
  return temp;
}

template <class T>
bool FlatIterator<T>::operator==(const FlatIterator<T>& other) {
  return ptr_ == other.ptr_;
}

template <class T>
bool FlatIterator<T>::operator!=(const FlatIterator<T>& other) {
  return ptr_ != other.ptr_;
}

}