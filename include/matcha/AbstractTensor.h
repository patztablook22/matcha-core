#pragma once

#include <vector>
#include <iostream>

#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
// #include <boost/archive/xml_iarchive.hpp>
// #include <boost/archive/xml_oarchive.hpp>

#include "matcha/range.h"

namespace matcha {

template <class T>
class AbstractTensor {

  public:

    AbstractTensor(const AbstractTensor& other);
    AbstractTensor(const Shape& shape, const std::vector<T>& data);
    AbstractTensor(const Shape& shape);
    AbstractTensor(ShapeInit shape);
    AbstractTensor();

    virtual Shape getShape() const = 0;

    virtual T& at(const Indices& indices) = 0;
    virtual T& at(const size_t position)  = 0;
    virtual AbstractTensor& chunk(const Range& range) = 0;

    virtual void add(AbstractTensor& other);
    virtual void subtract(AbstractTensor& other);
    virtual void multiply(AbstractTensor& other);
    virtual AbstractTensor& matmul(AbstractTensor& other) = 0;

    class Iterator;
    virtual Iterator begin() = 0;
    virtual Iterator end()   = 0;

    virtual size_t flatSize() const = 0;

  private:
    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version);

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
