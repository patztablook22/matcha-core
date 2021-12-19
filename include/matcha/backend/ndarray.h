#pragma once

#include <iostream>
#include <vector>
#include <initializer_list>

namespace matcha {
namespace backend {

template <class T>
class Ndarray {
  private:
    std::vector<T> data;
    std::vector<unsigned> shape;

  public:
    Ndarray();
    Ndarray(Ndarray& a);
    Ndarray(const std::vector<unsigned>& shape);
    Ndarray(std::initializer_list<unsigned>);

    T& at(const std::vector<unsigned>& indices);
    Ndarray chunk();

    Ndarray<T> add(Ndarray<T>& other);
    Ndarray<T> sub(Ndarray<T>& other);
    Ndarray<T> mul(Ndarray<T>& other);
    Ndarray<T> matmul(Ndarray<T>& other);

    template <class U> friend Ndarray<U> operator+(Ndarray<U>& a, Ndarray<U>& b);
    template <class U> friend Ndarray<U> operator*(Ndarray<U>& a, Ndarray<U>& b);
    template <class U> friend Ndarray<U> operator*(Ndarray<U>& t, U scalar);
    template <class U> friend Ndarray<U> operator*(U scalar, Ndarray<U>& t);

    template <class U> friend std::ostream& operator<<(std::ostream& os, Ndarray<U>& t);
/*
    template <class Scalar> friend Ndarray operator+(Ndarray&, Scalar);

    template <class Scalar> friend Ndarray operator+(Scalar, Ndarray&);

    // *
    friend Ndarray operator*(Ndarray&, Ndarray&);
    template <class Scalar> friend Ndarray operator*(Ndarray&, Scalar);
    template <class Scalar> friend Ndarray operator*(Scalar, Ndarray&);

    // /
    template <class Scalar> friend Ndarray operator/(Ndarray&, Scalar);
    */
   
  private:
    size_t getPosition(const std::vector<unsigned>& indices);

};

template class Ndarray<double>;
template class Ndarray<int>;

}
}