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
  buildFrom(std::vector<float>{value}, sizeof(float));
}

Tensor::Tensor(std::initializer_list<Tensor> tensors)
  : dtype_(tensors.begin()->dtype()),
    bytesPerElement_(tensors.begin()->bytesPerElement_),
    shape_(tensors.begin()->rank() + 1),
    buffer_(tensors.begin()->buffer_.size() * tensors.size()),
    from_(nullptr),
    to_(nullptr)
{
  shape_[0] = tensors.size();
  const Tensor& first = *tensors.begin();
  FlatIterator<float> flatTarget(at<float>(0));
  std::copy(first.shape_.begin(), first.shape_.end(), shape_.begin() + 1);
  for (const Tensor& tensor: tensors) {
    assert(std::equal(tensor.shape_.begin(), tensor.shape_.end(), shape_.begin() + 1));
    FlatIteration<const float, const Tensor> flatSource(tensor);
    for (auto& elem: flatSource) {
      *flatTarget = elem;
      flatTarget++;
    }
  }
}

Tensor::Tensor(Dtype dtype, const Shape& shape, const Buffer& buffer) 
  : dtype_(dtype),
    shape_(shape),
    buffer_(buffer),
    bytesPerElement_(bytesPerElement(dtype)),
    from_(nullptr),
    to_(nullptr)
{}

Tensor::Tensor(Dtype dtype, const Shape& shape) 
  : dtype_(dtype),
    shape_(shape),
    bytesPerElement_(bytesPerElement(dtype_)),
    buffer_(bytesPerElement(dtype) * std::accumulate(shape.begin(), shape.end(), 1, std::multiplies())),
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
  buildFrom(elements, sizeof(float));
}

Tensor::Tensor(const Shape& shape, const std::vector<int  >& elements)
  : dtype_(Dtype::Int),
    shape_(shape),
    from_(nullptr),
    to_(nullptr)
{
  buildFrom(elements, sizeof(int));
}

Tensor::Tensor(std::initializer_list<float> elements)
  : dtype_(Dtype::Float),
    shape_{(unsigned)elements.size()},
    from_(nullptr),
    to_(nullptr)
{
  buildFrom(std::vector<float>(elements), sizeof(float));
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
  buildFrom(flatElements, sizeof(float));
}

Tensor::Tensor(std::initializer_list<std::initializer_list<std::initializer_list<float>>> elements)
  : dtype_(Dtype::Float),
    from_(nullptr),
    to_(nullptr)
{
  std::vector<float> flatElements;
  for (auto& matrix: elements) {
    if (shape().size() != 0) assert(matrix.size() == shape()[1]);
    for (auto& row: matrix) {
      if (shape().size() == 0) shape_ = {(unsigned)elements.size(), (unsigned)matrix.size(), (unsigned)row.size()};
      else assert(row.size() == shape()[2]);
      flatElements.insert(flatElements.end(), row.begin(), row.end());
    }
  }
  buildFrom(flatElements, sizeof(float));
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

Tensor::Tensor(Tout& tout) {

}

template <class T>
T* Tensor::at(size_t position) {
  return reinterpret_cast<T*>(&buffer_[bytesPerElement_ * position]);
}

template <class T>
T* Tensor::at(const std::vector<int>& indices) {
  return at<T>(positionOf(indices));
}

template void * Tensor::at(size_t position);
template float* Tensor::at(size_t position);
template int  * Tensor::at(size_t position);

template void * Tensor::at(const std::vector<int>& indices);
template float* Tensor::at(const std::vector<int>& indices);
template int  * Tensor::at(const std::vector<int>& indices);

template <class T>
const T* Tensor::get(size_t position) const {
  return reinterpret_cast<const T*>(&buffer_[bytesPerElement_ * position]);
}

template <class T>
const T* Tensor::get(const std::vector<int>& indices) const {
  return get<T>(positionOf(indices));
}

template const void * Tensor::get(size_t position) const;
template const float* Tensor::get(size_t position) const;
template const int  * Tensor::get(size_t position) const;

template const void * Tensor::get(const std::vector<int>& indices) const;
template const float* Tensor::get(const std::vector<int>& indices) const;
template const int  * Tensor::get(const std::vector<int>& indices) const;

const Shape& Tensor::shape() const {
  return shape_;
}

void Tensor::reshape(const Shape& shape) {
  size_t oldFlatSize = size();
  size_t newFlatSize = std::accumulate(shape.begin(), shape.end(), 1, std::multiplies());
  assert(newFlatSize == oldFlatSize);
  shape_ = shape;
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

size_t Tensor::positionOf(const std::vector<int>& indices) const {
  assert(indices.size() == shape().size());
  size_t position = 0;
  for (int i = 0; i < indices.size() - 1; i++) {
    position += indices[i];
    position *= shape_[i + 1];
  }
  position += indices[indices.size() - 1];
  return position;
}

std::vector<int> Tensor::indicesOf(size_t position) const {
  auto ss = stepSizes();
  std::vector<int> indices(rank());
  std::transform(
    ss.begin(), ss.end(),
    indices.begin(),
    [&position](size_t stepSize) {
      int index = position / stepSize;
      position %= stepSize;
      return index;
    }
  );
  return indices;
}

std::vector<size_t> Tensor::stepSizes() const {
  std::vector<size_t> stepSizes(rank(), 1);
  std::reverse_copy(shape_.begin() + 1, shape_.end(), stepSizes.begin() + 1);
  std::partial_sum(stepSizes.begin(), stepSizes.end(), stepSizes.begin(), std::multiplies());
  std::reverse(stepSizes.begin(), stepSizes.end());
  return stepSizes;
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
      for (float elem: FlatIteration<const float, const Tensor>(tensor)) os << " " << elem;
      break;
    case Dtype::Int:
      for (int elem: FlatIteration<const int, const Tensor>(tensor)) os << " " << elem;
      break;
  }
  
  os << std::endl;
  return os;
}

unsigned Tensor::bytesPerElement(Dtype dtype) const {
  switch (dtype) {
    case Dtype::Float:
      return 4;
    case Dtype::Int:
      return 4;
    default:
      return 0;
  }
}
unsigned Tensor::bytesPerElement() const {
  return bytesPerElement_;
}

}