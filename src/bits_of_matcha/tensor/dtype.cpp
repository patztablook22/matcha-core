#include "bits_of_matcha/tensor/dtype.h"

namespace matcha {

Dtype::Dtype(Dtypes val)
  : val_(val)
{}

short Dtype::bytes() const {
  switch (val_) {
    case Dtypes::Int:
    case Dtypes::Float:
      return 4;
    case Dtypes::Double:
      return 8;
    case Dtypes::Bool:
      return 1;
    default:
      return 1;
  }
}

std::string Dtype::string() const {
  switch (val_) {
    case Dtypes::Int:
      return "Int";
    case Dtypes::Float:
      return "Float";
    case Dtypes::Double:
      return "Double";
    case Dtypes::Bool:
      return "Bool";
    default:
      return "???";
  }
}

Dtypes& Dtype::operator*() {
  return val_;
}

bool Dtype::operator==(const Dtype& other) const {
  return val_ == other.val_;
}

bool Dtype::operator!=(const Dtype& other) const {
  return !operator==(other);
}

}