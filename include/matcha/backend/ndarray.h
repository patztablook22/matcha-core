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

    class Iterator;
    matcha::AbstractTensor<T>::Iterator begin();
    matcha::AbstractTensor<T>::Iterator end();

  private:
    Indices shape;
    std::vector<T> data;

  private:
    size_t getPosition(const Indices& indices) const;
    size_t flatSize() const;
    
};

template class Ndarray<double>;
template class Ndarray<int>;

}
}