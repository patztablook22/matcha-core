#pragma once

namespace matcha {

class Index {
  public:
    Index(int from, int to);  // from...to
    Index(int index);         // from = index; to = index
    Index();                  // from = 0; to = -1

};

}