#pragma once

#include "matcha/fn/elementwisebinary.h"

namespace matcha {
namespace fn {

class Pow : public ElementWiseBinary {
  public:
    Pow(Tin a, Tin exponent);
  
  private:
    float runElement(float a, float b) override;

  private:
    float exponent_;
};

}
}