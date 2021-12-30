#include "matcha/data/batches.h"

#include "matcha/data/batch.h"
#include "matcha/data/instance.h"
#include "matcha/dataset/dataset.h"

#include <queue>

namespace matcha {
namespace data {

Batches::Batches(dataset::Dataset& dataset, size_t batchSize)
  : dataset_(dataset),
    batchSize_(batchSize)
{}

Batch Batches::next() {
  std::queue<Instance> instances;
  for (size_t i = 0; i < batchSize_; i++) {
    Instance instance = dataset_.next();
    if (!instance) break;
    instances.emplace(instance);
  }
  return Batch(instances);
}

}
}