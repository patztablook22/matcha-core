#include "matcha/AbstractTensor.h"

#include <iostream>
#include <algorithm>
#include <numeric>
#include <assert.h>
#include <list>
#include <execution>

#include <boost/serialization/vector.hpp>

#include "matcha/iterators/LinearIterator.h"

namespace matcha {


template <class T>
AbstractTensor<T>::AbstractTensor(const AbstractTensor& other) {}

template <class T>
AbstractTensor<T>::AbstractTensor(const Shape& shape, const std::vector<T>& data) {}

template <class T>
AbstractTensor<T>::AbstractTensor(const Shape& shape) {}

template <class T>
AbstractTensor<T>::AbstractTensor(ShapeInit shape) {}

template <class T>
AbstractTensor<T>::AbstractTensor() {}

template <class T>
void AbstractTensor<T>::add(AbstractTensor& other) {
  assert(getShape() == other.getShape());
  std::transform(
    // std::execution::par,
    begin(), end(), other.begin(), begin(),
    std::plus()
  );
}

template <class T>
void AbstractTensor<T>::subtract(AbstractTensor& other) {
  assert(getShape() == other.getShape());
  std::transform(begin(), end(), other.begin(), begin(), std::minus());
}

template <class T>
void AbstractTensor<T>::multiply(AbstractTensor& other) {
  assert(getShape() == other.getShape());
  std::transform(begin(), end(), other.begin(), begin(), std::multiplies());
}

template <class T>
AbstractTensor<T>::LinearIterator::LinearIterator(T* ptr)
  :ptr(ptr)
{}

template <class T>
AbstractTensor<T>::LinearIterator AbstractTensor<T>::LinearIterator::operator++() {
  ptr++;
  return *this;
}

template <class T>
AbstractTensor<T>::LinearIterator AbstractTensor<T>::LinearIterator::operator++(int) {
  auto temp = *this;
  ptr++;
  return temp;
}

template <class T>
AbstractTensor<T>::LinearIterator AbstractTensor<T>::LinearIterator::operator--() {
  ptr--;
  return *this;
}

template <class T>
AbstractTensor<T>::LinearIterator AbstractTensor<T>::LinearIterator::operator--(int) {
  auto temp = *this;
  ptr--;
  return temp;
}

template <class T>
bool AbstractTensor<T>::LinearIterator::operator==(const LinearIterator& other) {
  return ptr == other.ptr;
}

template <class T>
bool AbstractTensor<T>::LinearIterator::operator!=(const LinearIterator& other) {
  return ptr != other.ptr;
}

template <class T>
T& AbstractTensor<T>::LinearIterator::operator*() {
  return *ptr;
}

template <class T>
std::ostream& operator<<(std::ostream& os, AbstractTensor<T>& t) {
  os << '\n';
  auto shape = t.getShape();
  std::vector<size_t> breakpoints(shape.size(), 1);

  // shape = 2 3 4
  //       => 12 4 1
  for (int axis = breakpoints.size() - 1; axis >= 1; axis--) {
    breakpoints[axis - 1] = breakpoints[axis] * shape[axis];
  }

  for (size_t position = 0; T elem: t) {

    int indent = 0;
    for (size_t breakpoint: breakpoints) {
      if (position % breakpoint == 0) break;
      indent++;
    }

    if (position != 0)
      os << std::string(shape.size() - indent - 1, '\n');
    os << elem << " ";

    position++;
  }
  os << '\n';
  return os;
}

template <class T> template <class Archive>
void AbstractTensor<T>::serialize(Archive& ar, const unsigned int version) {
  Shape buffShape(getShape());
  std::vector<T> buffData(flatSize());
  auto iterFrom = begin();
  auto iterTo   = buffData.begin();
  while (iterFrom != end()) {
    *iterTo = *iterFrom;
    iterFrom++;
    iterTo  ++;
  }
  ar & buffShape;
  ar & buffData;
  iterFrom = begin();
  iterTo   = buffData.begin();
  while (iterFrom != end()) {
    *iterFrom = *iterTo;
    iterFrom++;
    iterTo  ++;
  }
}

template std::ostream& operator<<(std::ostream& os, AbstractTensor<double>& t);
template std::ostream& operator<<(std::ostream& os, AbstractTensor<int   >& t);

template void AbstractTensor<double>::serialize<boost::archive::text_oarchive>(boost::archive::text_oarchive& ar, const unsigned int);
template void AbstractTensor<int   >::serialize<boost::archive::text_oarchive>(boost::archive::text_oarchive& ar, const unsigned int);
template void AbstractTensor<double>::serialize<boost::archive::text_iarchive>(boost::archive::text_iarchive& ar, const unsigned int);
template void AbstractTensor<int   >::serialize<boost::archive::text_iarchive>(boost::archive::text_iarchive& ar, const unsigned int);

template void AbstractTensor<double>::serialize<boost::archive::binary_oarchive>(boost::archive::binary_oarchive& ar, const unsigned int);
template void AbstractTensor<int   >::serialize<boost::archive::binary_oarchive>(boost::archive::binary_oarchive& ar, const unsigned int);
template void AbstractTensor<double>::serialize<boost::archive::binary_iarchive>(boost::archive::binary_iarchive& ar, const unsigned int);
template void AbstractTensor<int   >::serialize<boost::archive::binary_iarchive>(boost::archive::binary_iarchive& ar, const unsigned int);

// template void AbstractTensor<double>::serialize<boost::archive::xml_oarchive>(boost::archive::xml_oarchive& ar, const unsigned int);
// template void AbstractTensor<int   >::serialize<boost::archive::xml_oarchive>(boost::archive::xml_oarchive& ar, const unsigned int);
// template void AbstractTensor<double>::serialize<boost::archive::xml_iarchive>(boost::archive::xml_iarchive& ar, const unsigned int);
// template void AbstractTensor<int   >::serialize<boost::archive::xml_iarchive>(boost::archive::xml_iarchive& ar, const unsigned int);

}