#include "matcha/fn/subtract.h"

namespace matcha {
namespace fn {

Subtract::Subtract(TIn a, TIn b) 
  : ElementWiseBinary(a, b)
{}

float Subtract::runElement(float a, float b) {
  return a - b;
}

}
}