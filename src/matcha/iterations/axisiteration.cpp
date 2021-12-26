#include "matcha/iterations/axisiteration.h"

#include <numeric>

#include "matcha/tensor.h"

namespace matcha {

template <class T, class Access>
AxisIteration<T, Access>::AxisIteration(Access& tensor, const int axis, void* ptr)
  : tensor_(tensor),
    axis_(axis)
{
  auto* bufferBegin = reinterpret_cast<T*>(&tensor.buffer_[0]);
  size_t position = reinterpret_cast<T*>(ptr) - bufferBegin;
  auto indices = tensor.indicesOf(position);
  indices[axis] = 0;
  beginPtr_ = bufferBegin + tensor.positionOf(indices);
  size_t stepSize = std::accumulate(
    tensor.shape().begin() + axis, tensor.shape().end(),
    1, std::multiplies()
  );
  endPtr_ = beginPtr_ + stepSize;
}

template <class T, class Access>
AxisIterator<T> AxisIteration<T, Access>::begin() {
  return AxisIterator<T>(tensor_, axis_, beginPtr_);
}

template <class T, class Access>
AxisIterator<T> AxisIteration<T, Access>::end() {
  return AxisIterator<T>(tensor_, axis_, endPtr_);
}

template class AxisIteration<float, Tensor>;
template class AxisIteration<int  , Tensor>;

template class AxisIteration<const float, const Tensor>;
template class AxisIteration<const int  , const Tensor>;

}