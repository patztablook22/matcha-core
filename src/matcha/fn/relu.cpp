#include "matcha/fn/relu.h"

namespace matcha {
namespace fn {

ReLU::ReLU(Tin a) 
  : ElementWiseUnary(a)
{}

float ReLU::runElement(float a) {
  return a > 0 ? a : 0;
}

}
}