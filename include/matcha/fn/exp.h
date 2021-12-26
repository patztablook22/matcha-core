#pragma once

#include "matcha/fn/elementwiseunary.h"

namespace matcha {
namespace fn {

class Exp : public ElementWiseUnary {
  public:
    Exp(Tin a);

  protected:
    float runElement(float a) override;

};

}
}