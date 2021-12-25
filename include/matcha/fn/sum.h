#pragma once

#include "matcha/fn/fn.h"

namespace matcha {
namespace fn {

class Sum : public Fn {
  public:
    Sum(TIn a);
    // Sum(TIn a, int alongAxis);

  protected:
    void run() override;

};

}
}