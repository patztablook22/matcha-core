#include "matcha/backend/ndarray.h"

#include <algorithm>
#include <numeric>

namespace matcha {
namespace backend {

template <class T>
Ndarray<T>::Ndarray(const AbstractTensor<T>& other)
  : shape(other.getShape()),
    data(flatSize())
{
}

template <class T>
Ndarray<T>::Ndarray(const Shape& shape, const std::vector<T>& data)
  : shape(shape),
    data(flatSize())
{
  assert(this->data.size() == data.size());
  std::copy(data.begin(), data.end(), begin());
}

template <class T>
Ndarray<T>::Ndarray(const Shape& shape) 
  : shape(shape),
    data(flatSize())
{}

template <class T>
Ndarray<T>::Ndarray(ShapeInit shape)
  : shape(shape.begin(), shape.end()),
    data(flatSize())
{}

template <class T>
Ndarray<T>::Ndarray() {}

template <class T>
Shape Ndarray<T>::getShape() const {
  return shape;
}

template <class T>
T& Ndarray<T>::at(const Indices& indicies) {
  return data[getPosition(indicies)];
}

template <class T>
T& Ndarray<T>::at(const size_t position) {
  return data[position];
}

template <class T>
Ndarray<T>& Ndarray<T>::chunk(const Range& range) {
  return *this;
}

template <class T>
AbstractTensor<T>::Iterator Ndarray<T>::begin() {
  typename AbstractTensor<T>::Iterator iter(&data[0]);
  return iter;
}

template <class T>
AbstractTensor<T>::Iterator Ndarray<T>::end() {
  typename AbstractTensor<T>::Iterator iter(&data[0] + data.size());
  return iter;
}

template <class T>
Ndarray<T>& Ndarray<T>::matmul(AbstractTensor<T>& other) {
  AbstractTensor<T>& a = *this;
  AbstractTensor<T>& b = other;
  const auto& aShape = a.getShape();
  const auto& bShape = b.getShape();

  // both must be at least matrices
  assert(aShape.size() >= 2 && bShape.size() >= 2);

  // (a,b) @ (b,c) = (a,c)
  int aRows = aShape[aShape.size() - 2];
  int aCols = aShape[aShape.size() - 1];
  int bRows = bShape[bShape.size() - 2];
  int bCols = bShape[bShape.size() - 1];
  // std::cout << thisRows << "x" << thisCols  << " "
  //           << otherRows << "x" << otherCols 
  //           << std::endl;
  assert(aCols == bRows);
  int cIter = aCols;
  int cRows = aRows;
  int cCols = bCols;

  // interpret tensor as multidimensional array of matrices
  // and multiply the matrices

  // => the matrix arrays must have equal shape
  assert(aShape.size() == bShape.size());
  Shape aPrematrixShape(aShape.begin(), aShape.end() - 2);
  Shape bPrematrixShape(bShape.begin(), bShape.end() - 2);
  for (auto bIter = bPrematrixShape.begin(); int aAxis: aPrematrixShape) {
    auto bAxis = *bIter++;
    assert(aAxis == bAxis);
  }
  Shape cMatrixShape(aPrematrixShape);
  cMatrixShape.push_back(cRows);
  cMatrixShape.push_back(cCols);
  
  auto* cPtr = new Ndarray<T>(cMatrixShape);
  auto& c = *cPtr;

  size_t aFlatSize = a.flatSize();
  size_t bFlatSize = b.flatSize();
  int aMatrixFlatSize = aRows * aCols;
  int bMatrixFlatSize = bRows * bCols;
  int cMatrixFlatSize = cRows * cCols;

  // for matrix in the array of matrices
  T buff;
  for (
    size_t aPosition  = 0, bPosition = 0, cPosition = 0;
           aPosition  < aFlatSize;
           aPosition += aMatrixFlatSize,
           bPosition += bMatrixFlatSize,
           cPosition += cMatrixFlatSize
  ) {
    // std::cout << "Matrix a start: " << aPosition << std::endl
    //           << "Matrix b start: " << bPosition << std::endl;

    // calculate every element
    for (int row = 0; row < cRows; row++) {
      for (int col = 0; col < cCols; col++) {
        buff = 0;
        for (int i = 0; i < cIter; i++) {
          const T& aOperand = a.at(aPosition + row * aCols + i);
          const T& bOperand = b.at(bPosition + i * bCols + col);
          buff += aOperand * bOperand;
        }
        c.at(cPosition + row * cCols + col) = buff;
      }
    }
  }

  return c;
}

template <class T>
Ndarray<T> Ndarray<T>::constant(const Shape& shape, const T& value) {
  auto* buff = new Ndarray(shape);
  std::fill(buff->begin(), buff->end(), value);
  return *buff;
}

template <class T>
Ndarray<T> Ndarray<T>::ones(const Shape& shape) {
  return constant(shape, 1);
}

template <class T>
Ndarray<T> Ndarray<T>::ones(ShapeInit shape) {
  return ones(shape);
}

template <class T>
size_t Ndarray<T>::getPosition(const Indices& indices) const {
  auto iter = shape.begin();
  bool valid = std::all_of(indices.begin(), indices.end(), 
    [&iter](int index) {
      return index >= 0 && index < *iter++;
    }
  );

  if (!valid) throw std::out_of_range("indices must be between 0 and dim - 1");

  size_t buff = indices[0];
  for (int axis = 1; axis < shape.size(); axis++) {
    buff *= shape[axis];
    buff += indices[axis];
  }
  return buff;
}

template <class T>
size_t Ndarray<T>::flatSize() const {
  return std::accumulate(shape.begin(), shape.end(), 1, std::multiplies());
}


}
}