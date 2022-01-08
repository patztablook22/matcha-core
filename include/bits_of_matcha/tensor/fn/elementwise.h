#pragma once

#include "bits_of_matcha/tensor/fn/fn.h"
#include <functional>

namespace matcha {
namespace fn {

class ElementWise : public Fn {
  public:
    ElementWise(ExprWrap a, ExprWrap b);

  protected:
    void init() override;
    void run() override;

  private:
    size_t flatSize_;
    int threads_;
};


}
}