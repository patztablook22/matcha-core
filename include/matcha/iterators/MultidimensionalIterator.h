#pragma once

#include "matcha/iterators/LinearIterator.h"

namespace matcha {

template <class T>
class AbstractTensor<T>::MultidimensionalIterator : public AbstractTensor<T>::LinearIterator {
  public:
    MultidimensionalIterator(AbstractTensor& tensor, const Indices& position);
    MultidimensionalIterator();
    void nextAlongAxis(int axis);
    void prevAlongAxis(int axis);

    void right();
    void left();
    void down();
    void up();
    void further();
    void closer();

    LinearIterator operator++() override;
    LinearIterator operator--() override;

    MultidimensionalIterator& operator=(const MultidimensionalIterator& other);

  protected:
    AbstractTensor& tensor;
    const std::vector<size_t> steps;
  
  private:
    static std::vector<size_t> getSteps(const Shape& shape);
};

template class AbstractTensor<double>::MultidimensionalIterator;
template class AbstractTensor<int   >::MultidimensionalIterator;

}