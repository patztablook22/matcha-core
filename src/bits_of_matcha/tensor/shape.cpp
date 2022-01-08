#include "bits_of_matcha/tensor/shape.h"

#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <iostream>

namespace matcha {
using namespace std;

Shape::Shape(unsigned size)
  : axes_(size, 0)
{}

Shape::Shape(std::initializer_list<unsigned> axes)
  : axes_(axes)
{}

size_t Shape::size() const {
  return axes_.size();
}

size_t Shape::volume() const {
  return std::accumulate(
    axes_.begin(),
    axes_.end(),
    1,
    std::multiplies()
  );
}

unsigned& Shape::operator[](int index) {
  if (index < 0) {
    index += axes_.size();
  }

  if (index < 0 || index >= axes_.size()) {
    throw std::out_of_range("index must be between -size and size-1");
  }

  return axes_[index];
}

std::vector<unsigned>::iterator Shape::begin() {
  return axes_.begin();
}

std::vector<unsigned>::iterator Shape::end() {
  // cout<< endl;
  // for (auto axis: axes_) cout << axis << " ";
  // cout << endl;
  return axes_.end();
}

bool Shape::operator==(const Shape& other) const {
  if (axes_.size() != other.axes_.size()) return false;
  return std::equal(axes_.begin(), axes_.end(), other.axes_.begin());
}

bool Shape::operator!=(const Shape& other) const {
  return !operator==(other);
}

std::string Shape::string() const {
  std::string temp = "{ ";
  for (int i = 0; i < size(); i++) {
    if (i != 0) temp += ", ";
    temp += std::to_string(axes_[i]);
  }
  temp += " }";
  return temp;
}


}