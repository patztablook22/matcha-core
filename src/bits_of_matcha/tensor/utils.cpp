#include "bits_of_matcha/tensor/utils.h"
#include "bits_of_matcha/tensor/expr.h"
#include "bits_of_matcha/tensor/tensor.h"
#include "bits_of_matcha/tensor/fn/fn.h"


#include <iostream>

namespace matcha {

ExprWrap::ExprWrap(const Tensor& tensor)
  : argxx::Wrap<Expr>(tensor)
{
  std::cout << " copy " << std::endl;
}

ExprWrap::ExprWrap(Tensor& tensor)
  : argxx::Wrap<Expr>(&tensor)
{}

ExprWrap::ExprWrap(Tensor* tensor)
  : argxx::Wrap<Expr>(tensor)
{}

ExprWrap::ExprWrap(const Expr& expr)
  : argxx::Wrap<Expr>(expr)
{}

ExprWrap::ExprWrap(Expr* expr)
  : argxx::Wrap<Expr>(expr)
{}

}