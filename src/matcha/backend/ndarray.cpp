#include "matcha/backend/ndarray.h"

#include <algorithm>
#include <numeric>

namespace matcha {
namespace backend {

template <class T>
Ndarray<T>::Ndarray() {
}

template <class T>
Ndarray<T>::Ndarray(Ndarray& a)
  : shape(a.shape),
    data(a.data)
{}

template <class T>
Ndarray<T>::Ndarray(const std::vector<unsigned>& shape)
  : shape(shape)
{
  size_t flat_size = std::accumulate(shape.begin(), shape.end(), 1, std::multiplies());
  data.resize(flat_size);
}

template <class T>
Ndarray<T>::Ndarray(std::initializer_list<unsigned> shape)
  : shape(shape)
{
  size_t flat_size = std::accumulate(shape.begin(), shape.end(), 1, std::multiplies());
  data.resize(flat_size);
}

template <class T> 
size_t Ndarray<T>::getPosition(const std::vector<unsigned>& indices) {
  size_t buff = 0;
  // will bug for some sizes e.g.
  for (int i = 0; i < indices.size(); i++) {
    buff += indices[i];
    buff *= shape[i];
  }
  return buff;
}

template <class T>
T& Ndarray<T>::at(const std::vector<unsigned>& indices) {
  return data[getPosition(indices)];
}

template <class T>
Ndarray<T> Ndarray<T>::add(Ndarray<T>& other) {
  Ndarray buff(*this);

  std::transform(
    data.begin(), data.end(),
    other.data.begin(),
    buff.data.begin(),
    std::plus()
  );

  return buff;
}

template <class T>
Ndarray<T> Ndarray<T>::sub(Ndarray<T>& other) {
  return Ndarray<T>{1, 2, 3};
}

template <class T>
Ndarray<T> Ndarray<T>::mul(Ndarray<T>& other) {
  return Ndarray<T>{1, 2, 3};
}

}
}