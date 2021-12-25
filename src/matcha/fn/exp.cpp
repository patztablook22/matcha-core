#include "matcha/fn/exp.h"

#include <cmath>

namespace matcha {
namespace fn {

Exp::Exp(TIn a) 
  : ElementWiseUnary(a)
{}

float Exp::runElement(float a) {
  return ::exp(a);
}

}
}