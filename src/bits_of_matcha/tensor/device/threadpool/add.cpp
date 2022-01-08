#include "bits_of_matcha/tensor/device/threadpool/add.h"

#include "bits_of_matcha/tensor/tensor.h"

#include <algorithm>
#include <numeric>
#include <execution>
#include <vector>
#include <thread>

namespace matcha {
namespace device {
namespace threadpool {

Add::Add(const Tensor& a, const Tensor& b, Tensor& c) 
  : abstract::Add(a, b, c)
{}

void Add::init() {
}

void Add::run() {
  std::vector<std::thread> threadpool;
  threadpool.reserve(threads_);

  auto begA = &a_.at<float>(0);
  auto endA = &a_.at<float>(0) + a_.size();
  auto begB = &b_.at<float>(0);
  auto begC = &c_.at<float>(0);

  size_t threadBeg = 0;
  size_t threadEnd = 0;
  size_t flatSize_ = a_.size();

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
}

}
}
}