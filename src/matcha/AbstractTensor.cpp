#include "matcha/AbstractTensor.h"

#include <iostream>
#include <algorithm>
#include <numeric>
#include <assert.h>


namespace matcha {

template <class T>
AbstractTensor<T>::AbstractTensor() {

}

template <class T>
AbstractTensor<T>::AbstractTensor(const AbstractTensor& other) {

}

template <class T>
void AbstractTensor<T>::add(AbstractTensor& other) {
  assert(getShape() == other.getShape());
  std::transform(begin(), end(), other.begin(), begin(), std::plus());
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
AbstractTensor<T>::Iterator::Iterator(T* ptr)
  :ptr(ptr)
{}

template <class T>
AbstractTensor<T>::Iterator AbstractTensor<T>::Iterator::operator++() {
  ptr++;
  return *this;
}

template <class T>
AbstractTensor<T>::Iterator AbstractTensor<T>::Iterator::operator++(int) {
  auto temp = *this;
  ptr++;
  return temp;
}

template <class T>
AbstractTensor<T>::Iterator AbstractTensor<T>::Iterator::operator--() {
  ptr--;
  return *this;
}

template <class T>
AbstractTensor<T>::Iterator AbstractTensor<T>::Iterator::operator--(int) {
  auto temp = *this;
  ptr--;
  return temp;
}

template <class T>
bool AbstractTensor<T>::Iterator::operator==(const Iterator& other) {
  return ptr == other.ptr;
}

template <class T>
bool AbstractTensor<T>::Iterator::operator!=(const Iterator& other) {
  return ptr != other.ptr;
}

template <class T>
T& AbstractTensor<T>::Iterator::operator*() {
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

template std::ostream& operator<<(std::ostream& os, AbstractTensor<double>& t);
template std::ostream& operator<<(std::ostream& os, AbstractTensor<int   >& t);

}