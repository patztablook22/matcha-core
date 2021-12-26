#pragma once

#include "matcha/fn/fn.h"

namespace matcha {
namespace fn {

class Sum : public Fn {
  public:
    Sum(Tin a);
    // Sum(Tin a, int alongAxis);

  protected:
    void run() override;

};

}
}