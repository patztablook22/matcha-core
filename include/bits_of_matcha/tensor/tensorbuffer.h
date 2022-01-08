#pragma once

#include <cstddef>
#include <memory>
#include <vector>
#include <iostream>

namespace matcha {

class TensorBuffer {
  public:

    TensorBuffer(size_t bytes = 0);

    template <class T>
    TensorBuffer(const std::vector<T>& elements);

    TensorBuffer(const TensorBuffer& other);

    ~TensorBuffer();

    void allocate(size_t bytes);

    std::byte& operator[](size_t index);
    const std::byte& operator[](size_t index) const;

    size_t bytes() const;
  
  private:
    size_t bytes_;
    std::byte* buffer_;

};

}