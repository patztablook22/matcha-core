#include "matcha/fn/multiply.h"

namespace matcha {
namespace fn {

Multiply::Multiply(TIn a, TIn b) 
  : ElementWiseBinary(a, b)
{}

float Multiply::runElement(float a, float b) {
  return a * b;
}

}
}