#pragma once

#include "matcha/fn/elementwisebinary.h"

namespace matcha {
namespace fn {

class Add : public ElementWiseBinary {
  public:
    Add(Tin a, Tin b);
    ~Add();
  
  private:
    float runElement(float a, float b) override;
};

}
}