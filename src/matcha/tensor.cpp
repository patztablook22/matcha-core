#include "matcha/tensor.h"

#include <algorithm>
#include <numeric>

#include "matcha/AbstractTensor.h"
#include "matcha/backend/ndarray.h"

namespace matcha {

template <class T>
backend::Ndarray<T> tensor(std::vector<int> const& shape) {
  std::vector<int> temp(shape);
  return backend::Ndarray<T>(temp);
}

template backend::Ndarray<double> tensor(std::vector<int> const& shape);
template backend::Ndarray<int   > tensor(std::vector<int> const& shape);

}