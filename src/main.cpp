#include <iostream>
#include <matcha.h>

int main() {
  using namespace matcha;

  auto ds = dataset::Csv("/home/patz/Downloads/mnist_train.csv");
  data::Batches batches(ds, 7);

  while (auto batch = batches.next()) {
    while (auto instance = batch.next()) {
      auto& [data, target] = instance;
    }
  }



  // {
  //   auto a = Fn(Val(3));
  //   cout << "should survive" << endl;
  // }
  // cout << "shouldn't survive" << endl;
  
  // return 0;
}