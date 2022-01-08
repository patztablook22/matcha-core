#include "bits_of_matcha/tensor/device/threadpool.h"

#include "bits_of_matcha/tensor/tensor.h"
#include "bits_of_matcha/tensor/device/threadpool/add.h"

#include "bits_of_matcha/tensor/device/cpu/add.h"
#include "bits_of_matcha/tensor/device/cpu/multiply.h"

namespace matcha {
namespace device {

ThreadPool::ThreadPool(int threads) {
  if (threads < 1) threads = 3;
  threads_ = threads;
}

std::shared_ptr<abstract::Computation> ThreadPool::add(const Tensor& a, const Tensor& b, Tensor& c) {
  if (threads_== 1) return std::make_shared<cpu::Add>(a, b, c);

  auto temp = new threadpool::Add(a, b, c);
  temp->threads_ = threads_;
  return std::shared_ptr<abstract::Add>(temp);
}

std::shared_ptr<abstract::Computation> ThreadPool::multiply(const Tensor& a, const Tensor& b, Tensor& c) {
  return std::make_shared<cpu::Multiply>(a, b, c);
}

}
}