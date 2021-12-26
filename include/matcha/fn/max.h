#pragma once

#include "matcha/fn/fn.h"

namespace matcha {
namespace fn {

class Max : public Fn {
  public:
    Max(Tin a);
    // Max(Tin a, int alongAxis);

  protected:
    void run() override;

};

}
}