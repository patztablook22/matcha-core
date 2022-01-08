#pragma once

#include "bits_of_matcha/tensor/fn/elementwise.h"

#include <memory>

namespace matcha {
namespace fn {

class Add : public ElementWise {
  public:
    ARGXX_INHERIT(Add, ElementWise)

    Add(ExprWrap a, ExprWrap b);

  private:
    void run() override;
    void init() override;
  
  private:
    std::shared_ptr<device::abstract::Computation> backend_;


};


}
}