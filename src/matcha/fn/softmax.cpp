#include "matcha/fn/softmax.h"

#include "matcha/fn/max.h"
#include "matcha/fn/subtract.h"
#include "matcha/fn/sum.h"
#include "matcha/fn/exp.h"
#include "matcha/fn/divide.h"

namespace matcha {
namespace fn {

Softmax::Softmax(TIn a) {
  inputs_.push_back(a);
  outputs_.push_back(
    new Tensor(a.tensor->dtype(), a.tensor->shape())
  );
  linkTensors();
}

void Softmax::run() {
  auto max = Max(*inputs_[0].tensor);
  auto optimized = Subtract(*inputs_[0].tensor, max.output(0));
  auto exp = Exp(optimized.output(0));
  auto& numerator = exp;
  auto denominator = Sum(exp.output(0));
  auto result = Divide(numerator.output(0), denominator.output(0));
  result.redirect(0, outputs_[0].tensor);
  result.eval();
}

}
}