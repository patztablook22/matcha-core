#include "matcha/fn/add.h"

namespace matcha {
namespace fn {

Add::Add(TIn a, TIn b) 
  : ElementWiseBinary(a, b)
{}

float Add::runElement(float a, float b) {
  return a + b;
}

}
}