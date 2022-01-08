#include "bits_of_matcha/tensor/fn/add.h"
#include "bits_of_matcha/tensor/tensor.h"

#include "bits_of_matcha/tensor/device/cpu.h"
#include "bits_of_matcha/tensor/device/threadpool.h"

#include <iostream>
using namespace std;

namespace matcha {
namespace fn {

Add::Add(ExprWrap a, ExprWrap b) 
  : ElementWise(a, b)
{}

void Add::init() {
  ElementWise::init();
  backend_ = device_->add(
    ins_[0]->cache(),
    ins_[1]->cache(),
    *cache_[0]
  );
}

void Add::run() {
  backend_->run();
}

}
}