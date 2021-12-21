#pragma once

#include <iostream>
#include <vector>
#include <initializer_list>

#include "matcha/AbstractTensor.h"
#include "matcha/iterators/LinearIterator.h"
#include "matcha/iterators/MultidimensionalIterator.h"

#include "matcha/backend/ndarray.h"

namespace matcha {

// target tensor is expected to have a default type
// using Tensor = backend::Ndarray<double>;

template <class T = double>
using Tensor = backend::Ndarray<T>;

}