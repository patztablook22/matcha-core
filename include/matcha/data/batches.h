#pragma once

#include <cstddef>

#include "matcha/data/instance.h"

namespace matcha {

namespace dataset {
  class Dataset;
}

namespace data {

class Batch;

class Batches {
  public:
    Batches(dataset::Dataset& dataset, size_t batchSize);

    Batch next();

  private:
    dataset::Dataset& dataset_;
    size_t batchSize_;
};

}
}