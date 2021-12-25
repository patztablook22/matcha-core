#pragma once

#include "matcha/fn/elementwiseunary.h"

namespace matcha {
namespace fn {

class ReLU : public ElementWiseUnary {
  public:
    ReLU(TIn a);

  protected:
    float runElement(float a) override;

};

}
}