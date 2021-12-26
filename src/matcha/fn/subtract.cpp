#include "matcha/fn/subtract.h"

namespace matcha {
namespace fn {

Subtract::Subtract(Tin a, Tin b) 
  : ElementWiseBinary(a, b)
{}

float Subtract::runElement(float a, float b) {
  return a - b;
}

}
}