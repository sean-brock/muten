#ifndef MUTEN_TENSOR_HPP
#define MUTEN_TENSOR_HPP

#include <memory>
#include <numeric>
#include <vector>

#include "allocator.hpp"
#include "device.hpp"
namespace muten {

template <typename T>
class Tensor {
 public:
  Tensor(const Device& device, const std::vector<int>& dim)
      : _device(device),
        _dim(dim),
        _strides(),
        _size(std::reduce(_dim.begin(), _dim.end(), 0, std::multiplies<T>{})),
        _allocator(get_allocator(_device.type)),
        _data(_allocator->allocate(_device.index, _size * sizeof(T))) {}

  virtual ~Tensor() = default;

  inline T* data() noexcept { return _data.get(); }
  inline const T* data() const noexcept { return _data.get(); }
  inline const std::vector<int>& dim() const noexcept { return _dim; }
  inline std::size_t num_elements() const noexcept { return _size; }
  inline const std::vector<int> stride() const noexcept { return _strides; }

 private:
  const Device _device;
  const std::vector<int> _dim;
  const std::vector<int> _strides;
  const std::size_t _size;
  Allocator* _allocator;
  std::shared_ptr<T> _data;
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
Tensor<T> zeros(const Device& device, const std::vector<int>& dim) {
  auto tensor = Tensor<T>(device, dim);
  return tensor;
}

};  // namespace tensor
};  // namespace muten

#endif
