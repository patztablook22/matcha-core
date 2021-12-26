#include "matcha/tensor.h"
#include "matcha/fn.h"
#include "matcha/iterations/flatiteration.h"

using namespace matcha;
using namespace matcha::fn;

#include <random>

int main() {

  std::random_device rd;
  std::mt19937 rng(rd());
  std::normal_distribution<float> gaussian(0, 1);

}