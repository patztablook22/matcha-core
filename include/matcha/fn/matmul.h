#pragma once

#include "matcha/fn/fn.h"
#include "matcha/iterators/axisiterator.h"

namespace matcha {
namespace fn {

class Matmul : public Fn {
  public:
    Matmul(Tin a, Tin b);
  
  protected:
    void run() override;
  
    size_t matrices;
    size_t rowsA, rowsB, rowsC;
    size_t colsA, colsB, colsC;
};

}
}