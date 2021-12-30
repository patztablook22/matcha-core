#include "matcha/dataset/csv.h"
#include "matcha/data/instance.h"

#include <fstream>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <regex>
#include <stdexcept>

#include "matcha/iterators/flatiterator.h"

namespace matcha {
namespace dataset {

Csv::Csv(const std::string& filepath, char horizontalDelimiter, char verticalDelimiter)
  : horizontalDelimiter_(horizontalDelimiter),
    verticalDelimiter_(verticalDelimiter),
    is_(new std::ifstream(filepath)),
    delete_(true),
    cols_(-1),
    rows_(-1)
{
  prepare();
}

Csv::Csv(std::istream& is, char horizontalDelimiter, char verticalDelimiter)
  : horizontalDelimiter_(horizontalDelimiter),
    verticalDelimiter_(verticalDelimiter),
    is_(&is),
    delete_(false),
    cols_(-1),
    rows_(-1)
{
  prepare();
}

std::vector<std::string> Csv::getRow() {
  std::string buffer;
  std::getline(*is_, buffer, verticalDelimiter_);
  std::stringstream streamRow(buffer);
  std::vector<std::string> row;
  if (cols_ != -1) row.reserve(cols_);
  while (std::getline(streamRow, buffer, horizontalDelimiter_)) {
    row.push_back(buffer);
  }
  rows_++;
  return row;
}

void Csv::prepare() {
  auto firstRow = getRow();
  cols_ = firstRow.size();
  head_ = firstRow;

  std::regex targetPattern("(label|class|category)");
  for (int colIndex = 0; std::string col: head_) {
    std::transform(col.begin(), col.end(), col.begin(), ::tolower);
    std::smatch matches;
    std::regex_search(col, matches, targetPattern);
    if (!matches.empty())
      targetCols_.push_back(colIndex);
    colIndex++;
  }
  deduceDataCols();
}

std::vector<std::string> Csv::targetCols() const {
  std::vector<std::string> buff;
  buff.reserve(targetCols_.size());
  for (int col: targetCols_) buff.push_back(head_[col]);
  return buff;
}

void Csv::setTargetCols(const std::vector<std::string>& targetCols) {
  std::vector<int> newTargetCols;
  for (auto& col: targetCols) {
    auto match = std::find(head_.begin(), head_.end(), col);
    if (match == head_.end()) throw std::invalid_argument("column not found");
    newTargetCols.push_back(match - head_.begin());
  }
  targetCols_ = newTargetCols;
  deduceDataCols();
}

void Csv::deduceDataCols() {
  dataCols_.clear();
  for (int col = 0; col < cols(); col++) {
    if (find(targetCols_.begin(), targetCols_.end(), col) == targetCols_.end())
      dataCols_.push_back(col);
  }
}

int Csv::cols() const {
  return cols_;
}

const std::vector<std::string>& Csv::head() const {
  return head_;
}

data::Instance Csv::next() {
  auto sRow = getRow();
  if (sRow.size() != cols()) return data::Instance();
  Tensor data(Dtype::Float, {(unsigned)dataCols_.size()});
  Tensor target(Dtype::Float, {(unsigned)targetCols_.size()});

  FlatIterator<float> iterData(data.at<float>(0));
  FlatIterator<float> iterTarget(target.at<float>(0));

  float temp;

  for (int col = 0; col < cols(); col++) {
    temp = std::stof(sRow[col]);
    if (std::find(targetCols_.begin(), targetCols_.end(), col) == targetCols_.end()) {
      *iterData++ = temp;
    } else {
      *iterTarget++ = temp;
    }
  }

  return data::Instance(data, target);
}

void Csv::reset() {
  is_->seekg(0);
  getRow();
}


}
}