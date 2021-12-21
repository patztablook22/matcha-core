#include "matcha/iterators/MultidimensionalIterator.h"

#include <algorithm>
#include <numeric>

namespace matcha {

template <class T>
AbstractTensor<T>::MultidimensionalIterator::MultidimensionalIterator(AbstractTensor& tensor, const Indices& position)
  : LinearIterator(&tensor.at(position)),
    tensor(tensor),
    steps(getSteps(tensor.getShape()))
{}

// template <class T>
// AbstractTensor<T>::MultidimensionalIterator::MultidimensionalIterator()
// {

// }

template <class T>
std::vector<size_t> AbstractTensor<T>::MultidimensionalIterator::getSteps(const Shape& shape) {
  std::vector<size_t> buff(shape.size(), 1);
  for (int i = buff.size() - 1; i >= 1; i--)
    buff[i - 1] = shape[i] * buff[i];
  return buff;
}

template <class T>
void AbstractTensor<T>::MultidimensionalIterator::nextAlongAxis(int axis) {
  assert(axis < steps.size());
  AbstractTensor<T>::LinearIterator::ptr += steps[axis];
}

template <class T>
void AbstractTensor<T>::MultidimensionalIterator::prevAlongAxis(int axis) {
  assert(axis < steps.size());
  AbstractTensor<T>::LinearIterator::ptr -= steps[axis];
}

template <class T>
void AbstractTensor<T>::MultidimensionalIterator::right() {
  nextAlongAxis(steps.size() - 1);  
}

template <class T>
void AbstractTensor<T>::MultidimensionalIterator::left() {
  prevAlongAxis(steps.size() - 1);  
}

template <class T>
void AbstractTensor<T>::MultidimensionalIterator::down() {
  nextAlongAxis(steps.size() - 2);  
}

template <class T>
void AbstractTensor<T>::MultidimensionalIterator::up() {
  prevAlongAxis(steps.size() - 2);  
}

template <class T>
void AbstractTensor<T>::MultidimensionalIterator::further() {
  nextAlongAxis(steps.size() - 3);  
}

template <class T>
void AbstractTensor<T>::MultidimensionalIterator::closer() {
  prevAlongAxis(steps.size() - 3);  
}

template <class T>
AbstractTensor<T>::LinearIterator AbstractTensor<T>::MultidimensionalIterator::operator++() {
  right();
  return *this;
}

template <class T>
AbstractTensor<T>::LinearIterator AbstractTensor<T>::MultidimensionalIterator::operator--() {
  left();
  return *this;
}

template <class T>
AbstractTensor<T>::MultidimensionalIterator& AbstractTensor<T>::MultidimensionalIterator::operator=(const AbstractTensor<T>::MultidimensionalIterator& other) {
  AbstractTensor<T>::LinearIterator::ptr = other.ptr;
  return *this;
}

}