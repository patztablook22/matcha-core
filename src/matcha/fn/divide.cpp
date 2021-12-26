#include "matcha/fn/divide.h"

namespace matcha {
namespace fn {

Divide::Divide(Tin a, Tin b) 
  : ElementWiseBinary(a, b)
{}

float Divide::runElement(float a, float b) {
  return a / b;
}

}
}