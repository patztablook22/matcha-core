#pragma once

#include "matcha/fn/fn.h"

namespace matcha {
namespace fn {

class ElementWiseBinary : public Fn {
  public:
    ElementWiseBinary(Tin a, Tin b);
  
  protected:
    void run() override;
    virtual float runElement(float a, float b) = 0;
};


}
}