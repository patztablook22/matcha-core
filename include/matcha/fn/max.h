#pragma once

#include "matcha/fn/fn.h"

namespace matcha {
namespace fn {

class Max : public Fn {
  public:
    Max(TIn a);
    // Max(TIn a, int alongAxis);

  protected:
    void run() override;

};

}
}