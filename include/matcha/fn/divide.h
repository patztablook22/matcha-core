#pragma once

#include "matcha/fn/elementwisebinary.h"

namespace matcha {
namespace fn {

class Divide : public ElementWiseBinary {
  public:
    Divide(Tin a, Tin b);
  
  private:
    float runElement(float a, float b) override;
};

}
}