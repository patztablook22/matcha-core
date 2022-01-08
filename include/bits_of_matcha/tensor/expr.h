#pragma once

#include "bits_of_matcha/tensor/utils.h"

#include <string>

namespace matcha {

class Tensor;

class Expr {
  protected:
    bool required_;
    ExprWraps ins_;
    ExprWraps outs_;

  public:
    ARGXX_MAKE(Expr);

    Expr(ExprWraps ins);
    Expr(const Expr& other);
    virtual ~Expr();

    virtual void eval() = 0;

    void require();
    bool required() const;

    virtual void linkOut(Expr* out);
    virtual void unlinkOut(Expr* out);

    virtual const Tensor& cache(int index = 0) const = 0;

};

}