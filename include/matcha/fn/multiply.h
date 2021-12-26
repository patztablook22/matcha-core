#pragma once

#include "matcha/fn/elementwisebinary.h"

namespace matcha {
namespace fn {

class Multiply : public ElementWiseBinary {
  public:
    Multiply(Tin a, Tin b);
  
  private:
    float runElement(float a, float b) override;
};

}
}
