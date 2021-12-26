#pragma once

#include "matcha/dtype.h"
#include "matcha/shape.h"
#include "matcha/index.h"
#include "matcha/buffer.h"

#include <iostream>
#include <memory>

namespace matcha {

class Tout;

namespace fn {
  class Fn;
}

class Tensor {
  public:
    // scalar
    Tensor(float value);

    // from tensors
    Tensor(std::initializer_list<Tensor> tensors);

    Tensor(Dtype dtype, const Shape& shape, const Buffer& buffer);
    Tensor(Dtype dtype, const Shape& shape);

    template <class T>
    Tensor(Dtype dtype, const Shape& shape, std::vector<T> elements, unsigned bytesPerElement);
    Tensor(const Shape& shape, const std::vector<float>& elements);
    Tensor(const Shape& shape, const std::vector<int  >& elements);

    // convenience initializers
    Tensor(std::initializer_list<float> elements);
    Tensor(std::initializer_list<std::initializer_list<float>> elements);
    Tensor(std::initializer_list<std::initializer_list<std::initializer_list<float>>> elements);

    // Tensor(const Edge& edge); // bind to given output edge
    Tensor(const Tout& tout);
    Tensor(Tout& tout);
    Tensor(fn::Fn& fn);

    // assign
    Tensor& operator=(const float value);

    // Tensor& get(std::vector<Index> indices);

    const Shape& shape() const;
    void reshape(const Shape& shape);

    template <class T = void> T* at(size_t position);
    template <class T = void> T* at(const std::vector<int>& indices);
    template <class T = void> const T* get(size_t position) const;
    template <class T = void> const T* get(const std::vector<int>& indices) const;

    bool scalar() const;
    unsigned rank() const;
    Dtype dtype() const;
    size_t size() const;

    void eval();
    void update();
    bool updated() const;

    size_t positionOf(const std::vector<int>& indices) const;
    std::vector<int> indicesOf(size_t position) const;

  protected:
    friend std::ostream& operator<<(std::ostream& os, const Tensor& tensor);
    Dtype  dtype_;
    Shape  shape_;

  private:
    Buffer buffer_;
    unsigned bytesPerElement_;

    template <class T, class Access> friend class FlatIteration;
    template <class T, class Access> friend class AxisIteration;

  public:
    bool updated_;
    fn::Fn* from_;
    fn::Fn* to_;
    friend class Fn;

  private:
    template <class T>
    void buildFrom(const std::vector<T>& elements, unsigned bytesPerElement);
    unsigned bytesPerElement() const;
    unsigned bytesPerElement(Dtype dtype) const;
    std::vector<size_t> stepSizes() const;
  
  public:
    std::string mark;
};

std::ostream& operator<<(std::ostream& os, const Tensor& tensor);

}