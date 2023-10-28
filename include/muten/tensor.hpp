#ifndef MUTEN_TENSOR_HPP
#define MUTEN_TENSOR_HPP

#include <memory>
#include <numeric>
#include <vector>

#include "device.hpp"
namespace muten {

template <typename T, Backend backend>
class Tensor {
 public:
  Tensor(int device_index, const std::vector<int>& sizes)
      : _sizes(sizes),
        _strides(_sizes),
        _size(
            std::reduce(_sizes.begin(), _sizes.end(), 0, std::multiplies<T>{})),

        _data(nullptr),
        _device_index(device_index) {
    std::size_t bytes = _size * sizeof(T);
    T* raw_data = static_cast<T*>(allocate<backend>(device_index, bytes));
    auto deleter = [device_index](T* ptr) {
      free<backend>(device_index, static_cast<void*>(ptr));
    };
    _data = std::shared_ptr<T>(raw_data, deleter);
  }

  // Tensor(const Tensor& tensor)
  //     : _sizes(tensor._sizes),
  //       _size(tensor._size),
  //       _strides(tensor._strides),
  //       _device(tensor._device) {}

  virtual ~Tensor() = default;

  inline T* data() noexcept { return _data.get(); }
  inline const T* data() const noexcept { return _data.get(); }
  inline const std::vector<int>& dim() const noexcept { return _sizes; }
  inline std::size_t num_elements() const noexcept { return _size; }
  inline const std::vector<int> stride() const noexcept { return _strides; }

 private:
  const std::vector<int> _sizes;
  const std::size_t _size;
  const std::vector<int> _strides;
  std::shared_ptr<T> _data;
  const int _device_index;
};

template <typename T, Backend backend>
T* begin(Tensor<T, backend>& t) {
  return t.data();
}

template <typename T, Backend backend>
const T* cbegin(const Tensor<T, backend>& t) {
  return t.data();
}

template <typename T, Backend backend>
T* end(Tensor<T, backend>& t) {
  return t.data() + t.size();
}

template <typename T, Backend backend>
const T* cend(const Tensor<T, backend>& t) {
  return t.data() + t.size();
}

namespace tensor {
template <typename T, Backend backend>
Tensor<T, backend> zeros(int device_index, const std::vector<int>& sizes) {
  auto tensor = Tensor<T, backend>(device_index, sizes);
  return tensor;
}

};  // namespace tensor
};  // namespace muten

#endif
