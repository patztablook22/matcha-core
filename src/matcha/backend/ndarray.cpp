#include "matcha/backend/ndarray.h"

#include <algorithm>
#include <numeric>

namespace matcha {
namespace backend {

template<class T>
Ndarray<T>::Ndarray(const AbstractTensor<T>& other)
  : shape(other.getShape()),
    data(flatSize())
{
}

template<class T>
Ndarray<T>::Ndarray(const Indices& shape) 
  : shape(shape),
    data(flatSize())
{}

template<class T>
Ndarray<T>::Ndarray() {

}

template <class T>
Ndarray<T>::Indices Ndarray<T>::getShape() const {
  return shape;
}

template <class T>
T& Ndarray<T>::at(const Indices& indicies) {
  T* buff = new T();
  return *buff;
}

template <class T>
Ndarray<T>& Ndarray<T>::chunk(const Indices& from, const Indices& to) {
  return *this;
}

template <class T>
Ndarray<T>::Iterator Ndarray<T>::begin() {
  return Iterator(&data[0]);
}

template <class T>
Ndarray<T>::Iterator Ndarray<T>::end() {
  return Iterator(&data[0] + data.size());
}

template <class T>
void Ndarray<T>::add(AbstractTensor<T>& other) {
}

template <class T>
size_t Ndarray<T>::getPosition(const Indices& indices) const {
  size_t buff = indices[0];
  for (int axis = 1; axis < shape.size(); axis++) {
    buff *= shape[axis];
    buff += indices[axis];
  }
  return buff;
}

template <class T>
size_t Ndarray<T>::flatSize() const {
  return std::accumulate(shape.begin(), shape.end(), 1, std::multiplies());
}

template <class T>
Ndarray<T>::Iterator::Iterator(T* ptr)
  :ptr(ptr)
{}

template <class T>
Ndarray<T>::Iterator Ndarray<T>::Iterator::operator++() {
  ptr++;
  return *this;
}

template <class T>
Ndarray<T>::Iterator Ndarray<T>::Iterator::operator++(int) {
  auto temp = *this;
  ptr++;
  return temp;
}

template <class T>
Ndarray<T>::Iterator Ndarray<T>::Iterator::operator--() {
  ptr--;
  return *this;
}

template <class T>
Ndarray<T>::Iterator Ndarray<T>::Iterator::operator--(int) {
  auto temp = *this;
  ptr--;
  return temp;
}

template <class T>
bool Ndarray<T>::Iterator::operator==(const Iterator& other) {
  return ptr == other.ptr;
}

template <class T>
bool Ndarray<T>::Iterator::operator!=(const Iterator& other) {
  return ptr != other.ptr;
}


}
}