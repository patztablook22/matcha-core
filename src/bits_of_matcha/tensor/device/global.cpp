#include "bits_of_matcha/tensor/device/global.h"
#include "bits_of_matcha/tensor/device/default.h"

namespace matcha {
namespace device {

Device& global() {
  static Default global_;
  return global_;
}

}
}