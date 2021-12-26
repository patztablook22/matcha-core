#include "matcha/fn/square.h"

namespace matcha {
namespace fn {

Square::Square(Tin a) 
  : ElementWiseUnary(a)
{}

float Square::runElement(float a) {
  return a * a;
}

}
}