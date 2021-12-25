#include "matcha/tensor.h"
#include "matcha/fn.h"

using namespace matcha;
using namespace matcha::fn;

Buffer floatsToBytes(const std::vector<float>& floats) {
  Buffer buffer(floats.size() * 4);
  return buffer;
}

int main() {
  std::vector<float> fv{0, 1, 2, 3, 4, 5, 6, 7, 0};
  Tensor a({3, 3}, fv);
  Tensor b({3, 3}, fv);
  Tensor c{{1, 2, 3},
           {1, 2, 3},
           {2, 3, 4}}; 

  // Tensor d{1, 2, 3};

  std::cout << a << b <<  c << std::endl;
  auto add1 = Add(&a, &b);
  auto add2 = Add(&c, add1.output(0));
  add2.output(0).tensor->mark = "a + b + c";
  auto powd = Pow(add2.output(0), .8);
  auto sum  = Sum(powd.output(0));
  auto soft = Softmax(powd.output(0));
  auto mult = Multiply(soft.output(0), -5);
  auto relu = ReLU(mult.output(0));
  Tensor& e = *powd.output(0).tensor;
  Tensor& f = *relu.output(0).tensor;

  f.eval();
  std::cout << e << f << std::endl;

  a = 0;
  b = 0;
  c = 0;
  a.update();

  f.eval();
  std::cout << f << std::endl;

  return 0;
}