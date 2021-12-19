#pragma once

#include <iostream>
#include <vector>

#include "matcha/AbstractTensor.h"

namespace matcha {
namespace backend {

template <class T>
class Ndarray : public AbstractTensor<T> {

  using Indices = std::vector<int>;

  public:
    Ndarray(const AbstractTensor<T>& other);
    Ndarray(const Indices& shape);
    Ndarray();

    Indices getShape() const override;

    T& at(const Indices& indices) override;
    Ndarray<T>& chunk(const Indices& from, const Indices& to) override;

    void add(AbstractTensor<T>& other) override;

    class Iterator;
    Iterator begin();
    Iterator end();

  private:
    Indices shape;
    std::vector<T> data;

  private:
    size_t getPosition(const Indices& indices) const;
    size_t flatSize() const;
    
};

template <class T>
class Ndarray<T>::Iterator {
  public:
    Iterator(T* ptr);
    Iterator operator++();
    Iterator operator++(int);
    Iterator operator--();
    Iterator operator--(int);
    T& operator*();
    bool operator==(const Iterator& other);
    bool operator!=(const Iterator& other);
  private:
    T* ptr;
};

template class Ndarray<double>;
template class Ndarray<int>;

}
}