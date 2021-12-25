#include "matcha/fn/square.h"

namespace matcha {
namespace fn {

Square::Square(TIn a) 
  : ElementWiseUnary(a)
{}

float Square::runElement(float a) {
  return a * a;
}

}
}