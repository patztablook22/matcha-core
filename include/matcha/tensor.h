#pragma once

#include <iostream>
#include <vector>
#include <initializer_list>

#include "matcha/backend/ndarray.h"

namespace matcha {

template <class T = double>
class Tensor {
  private:
    backend::Ndarray<T> backend;

  public:
    Tensor(std::initializer_list<unsigned>);
    Tensor(Tensor& t);

    template <class U> friend Tensor<U> operator+(Tensor<U>& a, Tensor<U>& b);
    template <class U> friend Tensor<U> operator*(Tensor<U>& a, Tensor<U>& b);
    template <class U> friend Tensor<U> operator*(Tensor<U>& t, U scalar);
    template <class U> friend Tensor<U> operator*(U scalar, Tensor<U>& t);

    template <class U> friend std::ostream& operator<<(std::ostream& os, Tensor<U>& t);
/*
    template <class Scalar> friend Tensor operator+(Tensor&, Scalar);

    template <class Scalar> friend Tensor operator+(Scalar, Tensor&);

    // *
    friend Tensor operator*(Tensor&, Tensor&);
    template <class Scalar> friend Tensor operator*(Tensor&, Scalar);
    template <class Scalar> friend Tensor operator*(Scalar, Tensor&);

    // /
    template <class Scalar> friend Tensor operator/(Tensor&, Scalar);
    */
};

template class Tensor<double>;
template class Tensor<int>;

}