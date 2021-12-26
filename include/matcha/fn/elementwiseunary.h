#pragma once

#include "matcha/fn/fn.h"

namespace matcha {
namespace fn {

class ElementWiseUnary : public Fn {
  public:
    ElementWiseUnary(Tin a);
  
  protected:
    void run() override;
    virtual float runElement(float a) = 0;
};


}
}