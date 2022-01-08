#include "bits_of_matcha/tensor/tensor.h"

#include "bits_of_matcha/tensor/iterations/flatiteration.h"
#include "bits_of_matcha/tensor/iterations/axisiteration.h"

#include <iostream>
using namespace std;

namespace matcha {

Tensor::Tensor(Dtype dtype, Shape shape)
  : Expr({})
  , dtype_(dtype)
  , shape_(shape)
  , buffer_(dtype.bytes() * shape.volume())
{}

Tensor::Tensor(Shape shape, const std::vector<float>& elements)
  : Expr({})
  , dtype_(Dtypes::Float)
  , shape_(shape)
  , buffer_(elements)
{
  if (shape_.volume() * dtype_.bytes() != buffer_.bytes())
    throw std::invalid_argument("tensor arguments are contradictory");
}

Tensor::Tensor(ExprWrap expr)
  : Expr({expr})
{
  expr->linkOut(this);

  auto& cache = expr->cache();
  dtype_  = cache.dtype();
  shape_  = cache.shape();
  buffer_.allocate(dtype_.bytes() * shape_.volume());

  // cout << "initiated linking out to " << this << endl;
}

Tensor::Tensor(float scalar)
  : Expr({})
  , dtype_(Dtypes::Float)
{}

Tensor::~Tensor() {
  for (auto& in: ins_) in->unlinkOut(this);
}

void Tensor::eval() {
  if (!required_) return;
  required_ = false;

  if (ins_.size() == 0) return;
  if (ins_.size() != 1) throw std::invalid_argument("tensor has more than 1 input");

  auto& in = *ins_[0];
  in.eval();

  auto& cacheBuffer = in.cache().buffer_;

  std::copy(
    &cacheBuffer[0], &cacheBuffer[cacheBuffer.bytes()],
    &buffer_[0]
  );

  // std::cout << "evaluating tensor " << this;
}

void Tensor::linkOut(Expr* out) {
  Expr::linkOut(out);
  // cout << "linking out tensor " << this << " to " << &*out << endl;
}

const Tensor& Tensor::cache(int index) const {
  return *this;
}



template <class T>
T& Tensor::at(size_t index) {
  T* ptr = reinterpret_cast<T*>(&buffer_[0]);
  return ptr[index];
}

template <class T>
const T& Tensor::at(size_t index) const {
  const T* ptr = reinterpret_cast<const T*>(&buffer_[0]);
  return ptr[index];
}

template float& Tensor::at(size_t);
template int  & Tensor::at(size_t);

template const float& Tensor::at(size_t) const;
template const int  & Tensor::at(size_t) const;

Dtype Tensor::dtype() const {
  return dtype_;
}

Shape Tensor::shape() const {
  return shape_;
}

size_t Tensor::size() const {
  return buffer_.bytes() / dtype_.bytes();
}

size_t Tensor::rank() const {
  return shape_.size();
}

template <class T>
FlatIteration<T, Tensor> Tensor::flatly() {
  return FlatIteration<T, Tensor>(*this);
}

template <class T>
FlatIteration<const T, const Tensor> Tensor::flatly() const {
  return FlatIteration<const T, const Tensor>(*this);
}

template FlatIteration<const float, const Tensor> Tensor::flatly() const;
template FlatIteration<float, Tensor> Tensor::flatly();

std::ostream& operator<<(std::ostream& os, const Tensor& tensor) {
  auto shape = tensor.shape();
  auto dtype = tensor.dtype();
  auto size  = tensor.size();

  os << "Tensor(" << '\n'
     << "  Dtype{ Dtypes::" << dtype.string() << " }," << '\n'
     << "  Shape{ ";

  for (auto it = shape.begin(); it != shape.end(); it++) {
    if (it != shape.begin()) {
      os << ", ";
    }
    os << *it;
  }

  os << " }," << '\n'
     << "  Elems{ ";

  if (tensor.rank() <= 1) {
    for (int i = 0; i < size; i++) {
      if (i != 0) os << ", ";
      switch(*dtype) {
        case Dtypes::Int:
          os << tensor.at<int>(i);
          break;
        case Dtypes::Float:
          os << tensor.at<float>(i);
          break;
      }
    }
  } else {
    size_t cols = shape[-1];
    size_t rows = shape[-2];
    for (int i = 0; i < size; i++) {
      if (i != 0) {
        os << ", ";
        if (i % (cols * rows) == 0) os << "\n";
      }
      if (i % cols == 0) os << "\n    ";
      switch (*dtype) {
        case Dtypes::Int:
          os << " " << tensor.at<int>(i);
          break;
        case Dtypes::Float:
          os << " " << tensor.at<float>(i);
          break;
      }
    }
    os << '\n' << " ";
  }
    
  os << " }" << '\n';
  os << ")" << std::endl;
  
  
  return os;
}

}