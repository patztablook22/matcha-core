#pragma once

#include "matcha/fn/elementwisebinary.h"

namespace matcha {
namespace fn {

class Multiply : public ElementWiseBinary {
  public:
    Multiply(TIn a, TIn b);
  
  private:
    float runElement(float a, float b) override;
};

}
}
