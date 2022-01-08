#pragma once

#include "bits_of_matcha/tensor/fn/elementwise.h"

#include <memory>

namespace matcha {
namespace fn {

class Multiply : public ElementWise {
  public:
    ARGXX_INHERIT(Multiply, ElementWise)

    Multiply(ExprWrap a, ExprWrap b);

  private:
    void run() override;
    void init() override;

  private:
    std::shared_ptr<device::abstract::Computation> backend_;
};


}
}