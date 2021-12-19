#include "matcha/tensor.h"

#include <algorithm>
#include <numeric>

#include "matcha/AbstractTensor.h"
#include "matcha/backend/ndarray.h"

namespace matcha {

template <class T>
backend::Ndarray<T> tensor() {
  return backend::Ndarray<T>();
}

template backend::Ndarray<double> tensor();
template backend::Ndarray<int   > tensor();

}