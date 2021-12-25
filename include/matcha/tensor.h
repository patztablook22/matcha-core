#pragma once

#include "matcha/dtype.h"
#include "matcha/shape.h"
#include "matcha/index.h"
#include "matcha/buffer.h"

#include <iostream>
#include <memory>

namespace matcha {

class TOut;

namespace fn {
  class Fn;
}

class Tensor {
  public:
    // scalar
    Tensor(float value);

    Tensor(Dtype dtype, const Shape& shape, const Buffer& buffer);
    Tensor(Dtype dtype, const Shape& shape);

    template <class T>
    Tensor(Dtype dtype, const Shape& shape, std::vector<T> elements, unsigned bytesPerElement);
    Tensor(const Shape& shape, const std::vector<float>& elements);
    Tensor(const Shape& shape, const std::vector<int  >& elements);

    // convenience initializers
    Tensor(std::initializer_list<float> elements);
    // Tensor(std::initializer_list<int  > elements);
    Tensor(std::initializer_list<std::initializer_list<float>> elements);
    // Tensor(std::initializer_list<std::initializer_list<int  >> elements);

    // Tensor(const Edge& edge); // bind to given output edge
    Tensor(const TOut& tout);
    Tensor(TOut& tout);
    Tensor(fn::Fn& fn);

    // assign
    Tensor& operator=(const float value);

    Tensor& get(std::vector<Index> indices);

    const Shape& shape() const;
    void reshape(const Shape& shape);

    bool scalar() const;
    unsigned rank() const;
    Dtype dtype() const;
    size_t size() const;

    void eval();
    void update();
    bool updated() const;

  protected:
    friend std::ostream& operator<<(std::ostream& os, const Tensor& tensor);
    Dtype  dtype_;
    Shape  shape_;

  private:
    Buffer buffer_;
    unsigned bytesPerElement_;

    template <class T> friend class FlatIteration;
    template <class T> friend class ConstFlatIteration;

  public:
    bool updated_;
    fn::Fn* from_;
    fn::Fn* to_;
    friend class Fn;

  private:
    template <class T>
    void buildFrom(const std::vector<T>& elements, unsigned bytesPerElement);
    unsigned bytesPerElement() const;
    // size_t bytesPerElement() const;
  
  public:
    std::string mark;
};

std::ostream& operator<<(std::ostream& os, const Tensor& tensor);

}