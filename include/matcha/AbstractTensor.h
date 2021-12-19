#pragma once

#include <vector>

namespace matcha {

template <class T>
class AbstractTensor {

  using Indices = std::vector<int>;

  public:
    AbstractTensor(const AbstractTensor& other);
    AbstractTensor(const Indices& shape);
    AbstractTensor();

    virtual Indices getShape() const = 0;

    virtual T& at(const Indices& indices) = 0;
    virtual AbstractTensor& chunk(const Indices& from, const Indices& to) = 0;

    virtual void add(AbstractTensor& other) = 0;
    // virtual void subtract(AbstractTensor& other);
    // virtual void multiply(AbstractTensor& other);
    // virtual void matrixMultiply(AbstractTensor& other);


};

template class AbstractTensor<double>;
template class AbstractTensor<int   >;

}