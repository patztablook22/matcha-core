#pragma once

#include <map>
#include <vector>
#include <thread>
#include <stack>

namespace matcha {

class Scope {
  public:
    Scope();
    ~Scope();

  private:
    static int counter;
    int id;

    static std::map<size_t, std::stack<Scope*>> threadStacks_;
    static std::stack<Scope *>& threadStack();
    static Scope global_;

};

}