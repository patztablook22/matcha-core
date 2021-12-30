#pragma once

#include "matcha/dataset/dataset.h"

#include <vector>
#include <iostream>

namespace matcha {

namespace data {
  class Instance;
}

namespace dataset {

class Csv : public Dataset {
  public:
    Csv(const std::string& filepath, char horizontalDelimiter = ',', char verticalDelimiter = '\n');
    Csv(std::istream& is, char horizontalDelimiter = ',', char verticalDelimiter = '\n');

    data::Instance next() override;
    void reset();

    std::vector<std::string> targetCols() const;
    void setTargetCols(const std::vector<std::string>& cols);

    int cols() const;
    const std::vector<std::string>& head() const;

  private:
    char horizontalDelimiter_;
    char verticalDelimiter_;
    std::istream* is_;
    bool delete_;

    std::vector<std::string> head_;

    int cols_;
    int rows_;
    std::vector<std::string> getRow();
    void prepare();

    std::vector<int> dataCols_;
    std::vector<int> targetCols_;

    void deduceDataCols();
};

}
}