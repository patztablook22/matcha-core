#include "matcha/tio.h"

#include "matcha/tensor.h"

namespace matcha {

Tin::Tin(const Tensor& value)
  : tensor(new Tensor(value)),
    referenced(false)
{
  std::cout << "Tin constructor" << std::endl;
}

Tin::Tin(const float scalar)
  : tensor(new Tensor(scalar)),
    referenced(false)
{
  std::cout << "Tin constructor" << std::endl;
}

Tin::Tin(Tensor* pointer) 
  : tensor(pointer),
    referenced(true)
{
  std::cout << "Tin constructor" << std::endl;
}

Tin::Tin(Tout& tout)
  : tensor(tout.tensor)
{
  std::cout << "Tin constructor" << std::endl;
}

Tin::~Tin() {
  std::cout << "Tin destructor" << std::endl;
}

Tout::Tout(Tensor* pointer)
  : tensor(pointer),
    referenced(true)
{
  std::cout << "Tout constructor" << std::endl;
}

Tout::~Tout() {
  std::cout << "Tout destructor" << std::endl;
}

}