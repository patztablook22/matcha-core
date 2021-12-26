#include "matcha/fn/exp.h"

#include <cmath>

namespace matcha {
namespace fn {

Exp::Exp(Tin a) 
  : ElementWiseUnary(a)
{}

float Exp::runElement(float a) {
  return ::exp(a);
}

}
}