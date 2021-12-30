#include "matcha/fn/add.h"

namespace matcha {
namespace fn {

Add::Add(Tin a, Tin b) 
  : ElementWiseBinary(a, b)
{
  std::cout << "Add constructor" << std::endl;
}

Add::~Add() {
  std::cout << "Add destructor" << std::endl;
}

float Add::runElement(float a, float b) {
  return a + b;
}

}
}