#include "bits_of_matcha/tensor/fn/multiply.h"
#include "bits_of_matcha/tensor/tensor.h"

#include "bits_of_matcha/tensor/device/cpu.h"
#include "bits_of_matcha/tensor/device/threadpool.h"

#include <iostream>
using namespace std;

namespace matcha {
namespace fn {

Multiply::Multiply(ExprWrap a, ExprWrap b) 
  : ElementWise(a, b)
{}

void Multiply::init() {
  ElementWise::init();
  backend_ = device_->multiply(
    ins_[0]->cache(),
    ins_[1]->cache(),
    *cache_[0]
  );
}

void Multiply::run() {
  backend_->run();
}

}
}