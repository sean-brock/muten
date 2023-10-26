#ifndef MUTEN_TENSOR_HPP
#define MUTEN_TENSOR_HPP

#include <memory>
#include <numeric>
#include <vector>

#include "cpu_device.hpp"
namespace muten {

template <typename T>
class Tensor {
 public:
  Tensor(const std::vector<int>& sizes)
      : _sizes(sizes),
        _strides(_sizes),
        _size(0),
        _device(CpuDevice()),
        _data(nullptr) {
    _size = std::reduce(_sizes.begin(), _sizes.end(), 0, std::multiplies<T>{});
    std::size_t bytes = _size * sizeof(T);
    _data = _device.allocate(bytes);
  }
  ~Tensor() { _device.free(_data); }
  T* data() noexcept;

 private:
  const std::vector<int> _sizes;
  const std::size_t _size;
  const std::vector<int> _strides;
  Device _device;
  T* _data;
};

template <typename T>
T* begin(Tensor<T>& t) {
  return t.data();
}

template <typename T>
const T* cbegin(const Tensor<T>& t) {
  return t.data();
}

template <typename T>
T* end(Tensor<T>& t) {
  return t.data() + t.size();
}

template <typename T>
const T* cend(const Tensor<T>& t) {
  return t.data() + t.size();
}

namespace tensor {
template <typename T>
Tensor<T> zeros(const std::vector<int>& sizes) {
  auto tensor = Tensor<T>(sizes);
  for (auto& elem : tensor) {
    elem = 0;
  }
  return tensor;
}

};  // namespace tensor
};  // namespace muten

#endif
