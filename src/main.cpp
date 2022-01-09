#include <tensor>
#include <chrono>

using namespace matcha;
using namespace matcha::fn;
using namespace std::chrono;

void hr(int level = 0) {
  char c;
  switch (level) {
    case 0:
      c = ' ';
      break;
    case 1:
      c = '-';
      break;
    case 2:
      c = '=';
      break;
  }
  std::cout << std::string(32, c) << std::endl;
}

ExprWrap operator+(const ExprWrap& a, const ExprWrap& b) {
  return Add(a, b);
}

ExprWrap operator*(const ExprWrap& a, const ExprWrap& b) {
  return Multiply(a, b);
}

Tensor get(Tensor& a) {
  Tensor c(5);
  return Tensor(
    Add(&a, Add(c, Add(c, &a)))
  );
}


void expr() {
  device::Default dev;
  Tensor a({4, 3}, {
    8, 2, 0,
    2, 2, 2,
    1, 1, 1,
    0, 0, 0
  });

}

void benchmark(float sizeCoef, float timeCoef, bool debug) {
  auto cpu  = device::Cpu();
  auto cpu2 = device::ThreadPool(1);
  auto pool = device::ThreadPool();

  size_t iterations = timeCoef * 1e5 / sizeCoef;

  Tensor a(Dtypes::Float, {(unsigned)sizeCoef, 100, 100});
  Tensor b(Dtypes::Float, {(unsigned)sizeCoef, 100, 100});

  // Tensor c = a + b;
  Tensor c(fn::Add(&a, &b));

  // for (auto& axis: a.shape()) cout << axis << " ";
  // cout << endl;
  // cout << iterations << " iterations" << endl;
  // exit(1);

  c.use(cpu);
  // cout << "------" << endl;


  for (int i = 0; i < iterations; i++) {
    a.require();
    c.eval();
  }
}


int main(int argc, char** argv) {
  // lazy();
  if (argc == 4) {
    float sizeCoef = ::stof(argv[1]);
    float timeCoef = ::stof(argv[2]);
    bool debug = ::stoi(argv[3]);
    benchmark(sizeCoef, timeCoef, debug);
  }
  // expr();


  return 0;
}