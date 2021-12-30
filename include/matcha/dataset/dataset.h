#pragma once

namespace matcha {

namespace data {
  class Instance;
}

namespace dataset {

class Dataset {
  public:
    virtual data::Instance next() = 0;
    virtual void reset() = 0;
};

}
}