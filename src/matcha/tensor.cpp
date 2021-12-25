#include "matcha/tensor.h"
#include "matcha/fn/fn.h"

#include <algorithm>
#include <numeric>
#include <assert.h>

#include "matcha/iterations/flatiteration.h"

namespace matcha {

Tensor::Tensor(float value)
  : dtype_(Dtype::Float),
    shape_(),
    from_(nullptr),
    to_(nullptr)
{
  buildFrom(std::vector<float>{value}, 4);
}

Tensor::Tensor(Dtype dtype, const Shape& shape, const Buffer& buffer) 
  : dtype_(dtype),
    shape_(shape),
    buffer_(buffer),
    from_(nullptr),
    to_(nullptr)
{}

Tensor::Tensor(Dtype dtype, const Shape& shape) 
  : dtype_(dtype),
    shape_(shape),
    buffer_(bytesPerElement() * std::accumulate(shape.begin(), shape.end(), 1, std::multiplies())),
    from_(nullptr),
    to_(nullptr)
{}

template <class T>
Tensor::Tensor(Dtype dtype, const Shape& shape, std::vector<T> elements, unsigned bytesPerElement)
  : dtype_(dtype),
    shape_(shape),
    from_(nullptr),
    to_(nullptr)
{
  buildFrom(elements, bytesPerElement);
}

Tensor::Tensor(const Shape& shape, const std::vector<float>& elements)
  : dtype_(Dtype::Float),
    shape_(shape),
    from_(nullptr),
    to_(nullptr)
{
  buildFrom(elements, 4);
}

Tensor::Tensor(const Shape& shape, const std::vector<int  >& elements)
  : dtype_(Dtype::Int),
    shape_(shape),
    from_(nullptr),
    to_(nullptr)
{
  buildFrom(elements, 4);
}

Tensor::Tensor(std::initializer_list<float> elements)
  : dtype_(Dtype::Float),
    shape_{(unsigned)elements.size()},
    from_(nullptr),
    to_(nullptr)
{
  buildFrom(std::vector<float>(elements), 4);
}

Tensor::Tensor(std::initializer_list<std::initializer_list<float>> elements)
  : dtype_(Dtype::Float),
    from_(nullptr),
    to_(nullptr)
{
  std::vector<float> flatElements;
  for (auto& row: elements) {
    if (shape().size() == 0) shape_ = {(unsigned)elements.size(), (unsigned)row.size()};
    else assert(row.size() == shape()[1]);
    flatElements.insert(flatElements.end(), row.begin(), row.end());
  }
  buildFrom(flatElements, 4);
}

Tensor& Tensor::operator=(const float value) {
  FlatIteration<float> flat(*this);
  for (auto& elem: flat) elem = value;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Tensor::eval() {
  if (!updated()) return;
  if (from_) from_->eval();
  updated_ = false;
}

bool Tensor::updated() const {
  return updated_;
}

void Tensor::update() {
  // std::cout << "updating tensor " << mark << std::endl;
  if (to_) to_->update();
  updated_ = true;
}

Tensor::Tensor(TOut& tout) {

}

const Shape& Tensor::shape() const {
  return shape_;
}

bool Tensor::scalar() const {
  return rank() == 0;
}

unsigned Tensor::rank() const {
  return shape_.size();
}

size_t Tensor::size() const {
  return buffer_.size() / bytesPerElement_;
}

Dtype Tensor::dtype() const {
  return dtype_;
}

template <class T>
void Tensor::buildFrom(const std::vector<T>& elements, unsigned bytesPerElement) {
  auto elementsBytes = reinterpret_cast<const std::byte*>(&elements[0]);
  size_t sizeBytes = elements.size() * bytesPerElement;
  buffer_ = Buffer(elementsBytes, elementsBytes + sizeBytes);
  bytesPerElement_ = bytesPerElement;
}

std::ostream& operator<<(std::ostream& os, const Tensor& tensor) {

  // dtype
  switch (tensor.dtype()) {
    case Dtype::Int:
      os << "Int";
      break;
    case Dtype::Float:
      os << "Float";
      break;
  }
  os << ";";

  // shape
  for (unsigned axis: tensor.shape()) os << " " << axis;
  os << ";";

  // elements
  switch (tensor.dtype()) {
    case Dtype::Float:
      for (float elem: ConstFlatIteration<float>(tensor)) os << " " << elem;
      break;
    case Dtype::Int:
      for (int elem: ConstFlatIteration<int>(tensor)) os << " " << elem;
      break;
  }
  
  os << std::endl;
  return os;
}

unsigned Tensor::bytesPerElement() const {
  switch (dtype()) {
    case Dtype::Float:
      return 4;
    case Dtype::Int:
      return 4;
    default:
      return 0;
  }
}

}