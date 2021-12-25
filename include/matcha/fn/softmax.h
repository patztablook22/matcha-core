#pragma once

#include "matcha/fn/fn.h"

namespace matcha {
namespace fn {

class Softmax : public Fn {
  public:
    Softmax(TIn a);

  protected:
    void run() override;

};

}
}