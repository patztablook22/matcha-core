#include "bits_of_matcha/tensor/utils.h"
#include "bits_of_matcha/tensor/expr.h"
#include "bits_of_matcha/tensor/tensor.h"
#include "bits_of_matcha/tensor/fn/fn.h"

#include <iostream>

namespace matcha {

ExprWrap::ExprWrap(const Tensor& tensor)
  : argxx::Wrap<Expr>(tensor)
{
  PP("copy tensor");
}

ExprWrap::ExprWrap(Tensor& tensor)
  : argxx::Wrap<Expr>(&tensor)
{
  PP("point to tensor");
}

ExprWrap::ExprWrap(Tensor* tensor)
  : argxx::Wrap<Expr>(tensor)
{
  PP("point to tensor");
}

ExprWrap::ExprWrap(const Expr& expr)
  : argxx::Wrap<Expr>(expr)
{
  PP("copy expr");
}

ExprWrap::ExprWrap(Expr* expr)
  : argxx::Wrap<Expr>(expr)
{
  PP("point to expr");
}

// ExprWrap::ExprWrap(const ExprWrap& other)
//   : argxx::Wrap<Expr>(other)
// {
//   PP("copy exprwrap");
// }


}