#pragma once

#include "matcha/fn/elementwiseunary.h"

namespace matcha {
namespace fn {

class Square : public ElementWiseUnary {
  public:
    Square(TIn a);
  
  private:
    float runElement(float a) override;
};

}
}