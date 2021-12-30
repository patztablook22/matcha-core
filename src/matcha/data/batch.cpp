#include "matcha/data/batch.h"

#include "matcha/data/instance.h"

namespace matcha {
namespace data {

Batch::Batch(const std::queue<Instance> instances)
  : instances_(instances),
    size_(instances_.size())
{}

size_t Batch::size() const {
  return size_;
}

Instance Batch::next() {
  // returns null instance (breaks while loops)
  if (instances_.empty()) return Instance();
  Instance instance = instances_.front();
  instances_.pop();
  return instance;
}

Batch::operator bool() const {
  return size_ != 0;
}

}
}