#pragma once

#include "matcha/fn/fn.h"

namespace matcha {
namespace fn {

class Accuracy : public Fn {
  public:
    Accuracy(Tin guess, Tin truth);

  protected:
    void run() override;

};

}
}