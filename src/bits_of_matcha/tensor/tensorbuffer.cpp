#include "bits_of_matcha/tensor/tensorbuffer.h"

#include "bits_of_matcha/tensor/dtype.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace matcha {

TensorBuffer::TensorBuffer(size_t bytes)
  : buffer_{nullptr}
  , bytes_{0}
{
  allocate(bytes);
}

template <class T>
TensorBuffer::TensorBuffer(const std::vector<T>& elements) 
  : buffer_{nullptr}
  , bytes_(0)
{
  auto beg = elements.begin();
  auto end = elements.end();
  auto byteBeg = reinterpret_cast<const std::byte*>(&*beg);
  auto byteEnd = reinterpret_cast<const std::byte*>(&*end);

  size_t bytes = byteEnd - byteBeg;
  allocate(bytes);
  std::copy(byteBeg, byteEnd, buffer_);
}

template TensorBuffer::TensorBuffer(const std::vector<float>&);
template TensorBuffer::TensorBuffer(const std::vector<int  >&);

TensorBuffer::TensorBuffer(const TensorBuffer& other)
  : buffer_{nullptr}
  , bytes_{other.bytes_}
{
  allocate(bytes_);
  std::copy(
    &other[0], &other[bytes_],
    &buffer_[0]
  );
}

TensorBuffer::~TensorBuffer() {
  if (buffer_ != nullptr) {
    delete[] buffer_;
    buffer_ = nullptr;
  }
}

void TensorBuffer::allocate(size_t bytes) {
  auto bufferNew = new std::byte[bytes];
  // ++buffers;
  auto bufferOld = buffer_;

  buffer_ = bufferNew;
  bytes_  = bytes;
  // todo: relocate buffer
  if (bufferOld != nullptr) {
    delete[] bufferOld;
  }
}

std::byte& TensorBuffer::operator[](size_t index) {
  return buffer_[index];
}

const std::byte& TensorBuffer::operator[](size_t index) const {
  return buffer_[index];
}

size_t TensorBuffer::bytes() const {
  return bytes_;
}

}