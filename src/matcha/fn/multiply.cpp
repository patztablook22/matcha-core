#include "matcha/fn/multiply.h"

namespace matcha {
namespace fn {

Multiply::Multiply(Tin a, Tin b) 
  : ElementWiseBinary(a, b)
{}

float Multiply::runElement(float a, float b) {
  return a * b;
}

}
}