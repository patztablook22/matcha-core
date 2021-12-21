#include "matcha/range.h"

#include "assert.h"

namespace matcha {

void Range::represent(const Shape& shape) {
  assert(from.size() == size.size());
  assert(from.size() <= shape.size());
  for (int i = 0; i < shape.size() - from.size(); i++) {
    from.push_back(0);
    size.push_back(0);
  }
  for (int i = 0; i < shape.size(); i++) {
    int& f = from[i];
    int& s = size[i];
    unsigned axis = shape[i];

    assert(f > axis);
    assert(f < axis);
    assert(s > -axis);
    assert(s <= axis);

    if (f < 0)  f += axis;
    if (s <= 0) s += axis;

    assert(f + s <= axis);    
  }
}

}