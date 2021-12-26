
#pragma once

#include "matcha/fn/elementwisebinary.h"

namespace matcha {
namespace fn {

class Subtract : public ElementWiseBinary {
  public:
    Subtract(Tin a, Tin b);
  
  private:
    float runElement(float a, float b) override;
};

}
}