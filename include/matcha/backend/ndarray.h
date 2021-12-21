#pragma once

#include <iostream>
#include <vector>

#include "matcha/AbstractTensor.h"

namespace matcha {
namespace backend {

template <class T = double>
class Ndarray : public AbstractTensor<T> {

  public:
    Ndarray(const AbstractTensor<T>& other);
    Ndarray(const Shape& shape, const std::vector<T>& data);
    Ndarray(const Shape& shape);
    Ndarray(ShapeInit shape);
    Ndarray();

    Shape getShape() const override;

    T& at(const Indices& indices) override;
    T& at(const size_t position)  override;
    Ndarray<T>& chunk(const Range& range) override;

    AbstractTensor<T>::Iterator begin();
    AbstractTensor<T>::Iterator end();

    Ndarray<T>& matmul(AbstractTensor<T>& other) override;

    static Ndarray<T> constant(const Shape& shape, const T& value);
    static Ndarray<T> ones(const Shape& shape);
    static Ndarray<T> ones(ShapeInit shape);

    size_t flatSize() const override;

  private:
    Shape shape;
    std::vector<T> data;

  private:
    size_t getPosition(const Indices& indices) const;
    
};

template class Ndarray<double>;
template class Ndarray<int>;

}
}