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
    Tout& output(unsigned index);
    unsigned outputs() const;

    void eval();
    void update();
    bool updated() const;

    void redirect(unsigned index, Tensor* tensor);

  protected:
    bool updated_;
    std::vector<Tin> inputs_;
    std::vector<Tout> outputs_;

  protected:
    virtual void run() = 0;

    void linkTensors();

  public:
    std::string mark;

};

}
}