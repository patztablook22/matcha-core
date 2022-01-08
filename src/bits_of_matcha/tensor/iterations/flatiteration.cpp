#include "bits_of_matcha/tensor/iterations/flatiteration.h"
#include "bits_of_matcha/tensor/iterators/flatiterator.h"
#include "bits_of_matcha/tensor/tensor.h"


namespace matcha {

template <class T, class Access>
FlatIteration<T, Access>::FlatIteration(Access& tensor)
  : tensor_(tensor)
{}

template <class T, class Access>
FlatIterator<T> FlatIteration<T, Access>::begin() {
  return FlatIterator<T>(
    reinterpret_cast<T*>(&tensor_.buffer_[0])
  );
}

template <class T, class Access>
FlatIterator<T> FlatIteration<T, Access>::end() {
  return FlatIterator(
    reinterpret_cast<T*>(&tensor_.buffer_[0] + tensor_.buffer_.bytes())
  );
}

}