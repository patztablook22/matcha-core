#include "bits_of_matcha/tensor/fn/elementwise.h"
#include "bits_of_matcha/tensor/tensor.h"

#include <stdexcept>
#include <iostream>
#include <thread>
using namespace std;

namespace matcha {
namespace fn {

ElementWise::ElementWise(ExprWrap a, ExprWrap b) 
  : Fn({a, b})
{}

void ElementWise::init() {
  const Tensor& a = ins_[0]->cache();
  const Tensor& b = ins_[1]->cache();

  if (a.shape() != b.shape())
    throw std::invalid_argument("shapes don't match");

  cache_.push_back(
    new Tensor(a.dtype(), a.shape())
  );

  flatSize_ = a.shape().volume();
  threads_ = 3;

}

void ElementWise::run() {
  auto begA = &*ins_[0]->cache().flatly<float>().begin();
  auto begB = &*ins_[1]->cache().flatly<float>().begin();
  auto begC = &*cache_[0]->flatly<float>().begin();

  auto endA = &*ins_[0]->cache().flatly<float>().end();
  auto endB = &*ins_[1]->cache().flatly<float>().end();
  auto endC = &*cache_[0]->flatly<float>().end();

  std::vector<std::thread> threadpool;
  threadpool.reserve(8);

  size_t threadBeg = 0;
  size_t threadEnd = 0;

  for (int thread = 0; thread < threads_; thread++) {

    if (thread == threads_ - 1) {
      threadEnd = threadBeg + flatSize_ / threads_;
    } else {
      threadEnd = flatSize_;
    }

    auto threadBegA = begA + threadBeg;
    auto threadBegB = begB + threadBeg;
    auto threadBegC = begC + threadBeg;

    auto threadEndA = begA + threadEnd;

    auto fn = [&]() {
      std::transform(
        threadBegA, threadEndA,
        threadBegB,
        threadBegC,
        std::plus()
      );
    };

    threadpool.emplace_back(fn);

  }

  for (auto& thread: threadpool) thread.join();
  // auto begA = &*ins_[0]->cache().flatly<float>().begin();
  // auto endA = &*ins_[0]->cache().flatly<float>().end();

  // auto begB = &*ins_[1]->cache().flatly<float>().begin();
  // auto begC = &*cache_[0]->flatly<float>().begin();

  // const float* a = begA;
  // const float* b = begB;
  // float* c = begC;
  // cout << "hey ";


}

}
}