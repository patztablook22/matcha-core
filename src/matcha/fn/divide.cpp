#include "matcha/fn/divide.h"

namespace matcha {
namespace fn {

Divide::Divide(TIn a, TIn b) 
  : ElementWiseBinary(a, b)
{}

float Divide::runElement(float a, float b) {
  return a / b;
}

}
}