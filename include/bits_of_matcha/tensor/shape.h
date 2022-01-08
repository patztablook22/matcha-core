#pragma once

#include <vector>
#include <initializer_list>
#include <string>

namespace matcha {

class Shape {
  public:
    Shape() = default;
    Shape(unsigned size);
    Shape(std::initializer_list<unsigned> axes);

    size_t size() const;
    size_t volume() const;

    unsigned& operator[](int index);

    std::vector<unsigned>::iterator begin();
    std::vector<unsigned>::iterator end();

    bool operator==(const Shape& other) const;
    bool operator!=(const Shape& other) const;

    std::string string() const;

  private:
    std::vector<unsigned> axes_;
};

};