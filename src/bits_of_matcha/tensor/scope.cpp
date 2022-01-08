#include "bits_of_matcha/tensor/scope.h"

#include <thread>

#include <iostream>
using namespace std;

namespace matcha {

std::map<size_t, std::stack<Scope *>> Scope::threadStacks_ = {};
int Scope::counter = 0;

Scope::Scope() {
  auto& scopes = threadStack();
  scopes.push(this);
}

Scope::~Scope() {
  auto& scopes = threadStack();
  scopes.pop();
}

std::stack<Scope *>& Scope::threadStack() {
  size_t threadId = std::hash<std::thread::id>{}(std::this_thread::get_id());
  auto& temp = threadStacks_[threadId];
  return temp;
}

}