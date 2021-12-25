#include "matcha/iterations/flatiteration.h"
#include "matcha/tensor.h"

namespace matcha {

template <class T>
FlatIteration<T>::FlatIteration(Tensor& tensor)
  : tensor_(&tensor)
{}

template <class T>
FlatIterator<T> FlatIteration<T>::begin() {
  return FlatIterator(
    reinterpret_cast<T*>(&tensor_->buffer_[0])
  );
}

template <class T>
FlatIterator<T> FlatIteration<T>::end() {
  return FlatIterator(
    reinterpret_cast<T*>(&tensor_->buffer_[0] + tensor_->buffer_.size())
  );
}

template <class T>
ConstFlatIteration<T>::ConstFlatIteration(const Tensor& tensor)
  : tensor_(&tensor)
{}

template <class T>
FlatIterator<const T> ConstFlatIteration<T>::begin() {
  return FlatIterator(
    reinterpret_cast<const T*>(&tensor_->buffer_[0])
  );
}

template <class T>
FlatIterator<const T> ConstFlatIteration<T>::end() {
  return FlatIterator(
    reinterpret_cast<const T*>(&tensor_->buffer_[0] + tensor_->buffer_.size())
  );
}

}