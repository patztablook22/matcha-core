#pragma once

#include <iostream>
#include <vector>
#include <initializer_list>

#include "matcha/AbstractTensor.h"
#include "matcha/backend/ndarray.h"

namespace matcha {

template<class T = double>
backend::Ndarray<T> tensor(std::vector<int> const& shape);
// template<class T = double>
// backend::Ndarray<T>& tensor(std::initializer_list<unsigned> shape);

}