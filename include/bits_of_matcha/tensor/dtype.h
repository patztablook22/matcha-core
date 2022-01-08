#pragma once

#include <string>

namespace matcha {

enum class Dtypes {
  Int,
  Float,
  Double,
  Bool,
};

class Dtype {
  public:
    Dtype(Dtypes val);
    Dtype() = default;

    Dtypes& operator*();

    short bytes() const;
    std::string string() const;

    bool operator==(const Dtype& other) const;
    bool operator!=(const Dtype& other) const;


  private:
    Dtypes val_;
};

}