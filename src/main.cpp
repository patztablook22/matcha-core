#include <matcha>
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

void asdf(const Tensor& t) {

}

auto x4(const ExprWrap x) {
  return x + x + x + x;
}


void expr() {
  Tensor a({4, 3}, {
    8, 2, 0,
    2, 2, 2,
    1, 1, 1,
    0, 0, 0
  });
  Tensor b({4, 3}, {
    1, 2, 3,
    4, 4, 4,
    1, 2, 2,
    0, 0, 1
  });

  Tensor c = a * b * a * a;
  c.eval();
  cout << c;

  a.at<float>(0) = -10;
  a.require();
  c.eval();
  cout << c;


}

void tensor() {
  Tensor a(
    3
  );
}

void benchmark() {
  auto cpu  = device::Cpu();
  auto cpu2 = device::ThreadPool(1);
  auto pool = device::ThreadPool();

  Tensor a(Dtypes::Float, {100, 100});
  Tensor b(Dtypes::Float, {100, 100});

  Tensor c = a + b;

  // c.use(cpu);


  for (int i = 0; i < 1'000'000; i++) {
    a.require();
    c.eval();
  }
}

void lazy() {
  Tensor a(Dtypes::Float, {1'000, 100, 100});
  Tensor b(Dtypes::Float, {1'000, 100, 100});

  auto cpu  = device::Cpu();
  auto pool = device::ThreadPool();

  auto c = a + b;
  c->use(cpu);

  auto d = c * a;
  d->use(pool);

}

int main() {
  // lazy();
  benchmark();


  return 0;
}

  // auto start = high_resolution_clock::now();
  // auto stop = high_resolution_clock::now();
  // auto duration = duration_cast<milliseconds>(stop - start);
  // // cout << duration.count() << " ms" << endl;
