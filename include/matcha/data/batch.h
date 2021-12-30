#pragma once

#include <queue>

namespace matcha {
namespace data {

class Instance;

class Batch {
  public:
    Batch(std::queue<Instance> instances);

    size_t size() const;

    Instance next();

    operator bool() const;
  
  private:
    std::queue<Instance> instances_;
    size_t size_;

};

}
}