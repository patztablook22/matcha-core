#include "matcha/tensor.h"

#include <algorithm>
#include <numeric>

namespace matcha {

template <class T>
Tensor<T>::Tensor(std::initializer_list<unsigned> shape)
{
}

template <class U>
Tensor<U> operator+(Tensor<U>& a, Tensor<U>& b) {
  return Tensor<U>{1, 2, 3};
}

template <class U>
Tensor<U> operator*(Tensor<U>& a, Tensor<U>& b) {
  return Tensor<U>{1, 2, 3};
}

template <class U>
Tensor<U> operator*(Tensor<U>& t, U scalar) {
  return Tensor{1, 2, 3};
}

template <class U>
Tensor<U> operator*(U scalar, Tensor<U>& t) {
  return operator+(t, scalar);
}

template <class U>
std::ostream& operator<<(std::ostream& os, Tensor<U>& t) {
  return os;
}

template Tensor<double> operator+<double>(Tensor<double>& a, Tensor<double>& b);
template Tensor<int   > operator+<int   >(Tensor<int   >& a, Tensor<int   >& b);

template Tensor<double> operator*<double>(Tensor<double>& a, Tensor<double>& b);
template Tensor<int   > operator*<int   >(Tensor<int   >& a, Tensor<int   >& b);

template std::ostream& operator<<(std::ostream& os, Tensor<double>& t);
template std::ostream& operator<<(std::ostream& os, Tensor<int   >& t);

}