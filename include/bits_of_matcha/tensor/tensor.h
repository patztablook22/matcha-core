#pragma once

#include "bits_of_matcha/tensor/expr.h"

#include <initializer_list>
#include <iostream>

#include "bits_of_matcha/tensor/dtype.h"
#include "bits_of_matcha/tensor/shape.h"
#include "bits_of_matcha/tensor/tensorbuffer.h"

#include "bits_of_matcha/tensor/iterations/flatiteration.h"
#include "bits_of_matcha/tensor/iterations/axisiteration.h"

namespace matcha {

template <class T, class Access>
class FlatIteration;

template <class T, class Access>
class AxisIteration;

class Tensor : public Expr {
  public:
    ARGXX_INHERIT(Tensor, Expr);

    // as ndarray
    Tensor(Dtype dtype, Shape shape);


    Tensor(Shape shape, const std::vector<float>& elements);

    // as expression
    Tensor(ExprWrap expr);
    Tensor(float scalar);

    ~Tensor();

    void eval() override;

    template <class T>
    T& at(size_t index);

    template <class T>
    const T& at(size_t index) const;

    Dtype dtype() const;
    Shape shape() const;

    size_t size() const;
    size_t rank() const;

    // iterations

    template <class T>
    FlatIteration<T, Tensor> flatly();

    template <class T>
    FlatIteration<const T, const Tensor> flatly() const;

    void linkOut(Expr* out) override;
    const Tensor& cache(int index = 0) const override;

  private:
    Dtype dtype_;
    Shape shape_;
    TensorBuffer buffer_;

  private:
    template <class T>
    void buildFromElements(const std::vector<T>&);

    friend std::ostream& operator<<(std::ostream& os, const Tensor& tensor);

    template <class T, class Access>
    friend class FlatIteration;

    template <class T, class Access>
    friend class AxisIteration;
};

}