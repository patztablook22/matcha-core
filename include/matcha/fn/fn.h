#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <initializer_list>

#include "matcha/tensor.h"
#include "matcha/tio.h"

namespace matcha {
namespace fn {

class Fn {
  public:
    Fn();
    TOut& output(unsigned index);
    unsigned outputs() const;

    void propagateRequired();
    void propagateUpdateNeeded();

    void eval();
    void update();
    bool updated() const;

    void redirect(unsigned index, Tensor* tensor);

  protected:
    bool updated_;
    std::vector<TIn> inputs_;
    std::vector<TOut> outputs_;

  protected:
    virtual void run() = 0;
    void linkTensors();

  public:
    std::string mark;

};

}
}