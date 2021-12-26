#include "matcha/fn/matmul.h"

#include <cassert>
#include <numeric>

#include "matcha/iterations/axisiteration.h"

namespace matcha {
namespace fn {

Matmul::Matmul(Tin a, Tin b) {
  const Shape& shapeA = a.tensor->shape();
  const Shape& shapeB = b.tensor->shape();
  const int& rankA = shapeA.size();
  const int& rankB = shapeB.size();

  assert(rankA == rankB);
  assert(rankA >= 2);
  assert(std::equal(shapeA.begin(), shapeA.end() - 2, shapeB.begin()));
  matrices = std::accumulate(shapeA.begin(), shapeA.end() - 2, 1, std::multiplies());

  colsA = shapeA[rankA - 1];
  rowsA = shapeA[rankA - 2];
  colsB = shapeB[rankB - 1];
  rowsB = shapeB[rankB - 2];

  assert(colsA == rowsB);

  rowsC = rowsA;
  colsC = colsB;
  Shape shapeC = shapeA;
  const int& rankC = rankA;

  shapeC[rankC - 1] = colsC;
  shapeC[rankC - 2] = rowsC;

  inputs_.push_back(a);
  inputs_.push_back(b);
  outputs_.push_back(
    new Tensor(a.tensor->dtype(), shapeC)
  );
  linkTensors();
}

void Matmul::run() {
  const Tensor& tensorA = *inputs_[0].tensor;
  const Tensor& tensorB = *inputs_[1].tensor;
  Tensor& tensorC = *outputs_[0].tensor;

  AxisIterator<const float> matrixA(tensorA, tensorA.rank() - 3, tensorA.get<float>(0));
  AxisIterator<const float> matrixB(tensorB, tensorB.rank() - 3, tensorB.get<float>(0));
  AxisIterator<      float> matrixC(tensorC, tensorC.rank() - 3, tensorC.at<float>(0));
  
  for (size_t matrix = 0; matrix < matrices; matrix++) {
    AxisIterator<const float> rowA(tensorA, tensorA.rank() - 2, &(*matrixA));
    AxisIterator<      float> rowC(tensorC, tensorC.rank() - 2, &(*matrixC));
    for (size_t row = 0; row < rowsC; row++) {
      AxisIterator<const float> colB(tensorB, tensorB.rank() - 1, &(*matrixB));
      AxisIterator<      float> colC(tensorC, tensorC.rank() - 1, &(*rowC));
      for(size_t col = 0; col < colsC; col++) {
        AxisIterator<const float> colA(tensorA, tensorA.rank() - 1, &(*rowA));
        AxisIterator<const float> rowB(tensorB, tensorB.rank() - 2, &(*colB));
        // std::cout << *colA << " " << *rowB << std::endl;

        // int tmp = std::inner_product(
        //   colA, colA + colsA,
        //   rowB,
        //   0
        // );
        float tmp = 0;
        for (int i = 0; i < colsA; i++) {
          tmp += *colA * *rowB;
          colA++;
          rowB++;
        }
        *colC = tmp;
        // std::cout << tmp << std::endl;

        colB++;
        colC++;
      }

      rowA++;
      rowC++;
    }

    matrixA++;
    matrixB++;
    matrixC++;
  }
}

}
}