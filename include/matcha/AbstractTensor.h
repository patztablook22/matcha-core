#pragma once

#include <vector>
#include <iostream>

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

    virtual void add(AbstractTensor& other);
    virtual void subtract(AbstractTensor& other);
    virtual void multiply(AbstractTensor& other);
    // virtual void matrixMultiply(AbstractTensor& other);

    class Iterator;
    virtual Iterator begin() = 0;
    virtual Iterator end()   = 0;

};

template <class T>
class AbstractTensor<T>::Iterator {
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

template class AbstractTensor<double>;
template class AbstractTensor<int   >;

template <class T>
std::ostream& operator<<(std::ostream& os, AbstractTensor<T>& t);

}