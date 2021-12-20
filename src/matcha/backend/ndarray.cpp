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
  return data[getPosition(indicies)];
}

template <class T>
Ndarray<T>& Ndarray<T>::chunk(const Indices& from, const Indices& to) {
  return *this;
}

template <class T>
matcha::AbstractTensor<T>::Iterator Ndarray<T>::begin() {
  typename AbstractTensor<T>::Iterator iter(&data[0]);
  return iter;
}

template <class T>
matcha::AbstractTensor<T>::Iterator Ndarray<T>::end() {
  typename AbstractTensor<T>::Iterator iter(&data[0] + data.size());
  return iter;
}

template <class T>
size_t Ndarray<T>::getPosition(const Indices& indices) const {
  bool valid = std::all_of(indices.begin(), indices.end(), 
    [this](int index) {
      return index >= 0 && index < this->shape.size();
    }
  );

  if (!valid) throw std::out_of_range("indices must be between 0 and dim - 1");

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


}
}