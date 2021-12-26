#include "matcha/fn/pow.h"
#include <cmath>

namespace matcha {
namespace fn {

Pow::Pow(Tin a, Tin exponent) 
  : ElementWiseBinary(a, exponent)
{}

float Pow::runElement(float a, float b) {
  return ::pow(a, b);
}

}
}