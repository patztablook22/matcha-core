#pragma once

static int relocated = 0;
static int buffers = 0;

#include <argxx>


#include <iostream>
using namespace std;

namespace matcha {

class Expr;
class Tensor;
class Fn;

class ExprWrap : public argxx::Wrap<Expr> {
  public:
    ExprWrap(const Tensor& tensor);
    ExprWrap(Tensor& tensor);
    ExprWrap(Tensor* tensor);

    ExprWrap(const Expr& fn);
    ExprWrap(Expr* fn);

    // ExprWrap(const ExprWrap& other);

    // const ExprWrap& operator=(const ExprWrap& other);

};

// using ExprWrap  = argxx::Wrap<Expr>;
// using ExprWraps = argxx::Wraps<Expr>;
using ExprWraps = std::vector<ExprWrap>;
// using ExprArgs  = argxx::Args<Expr>;

}