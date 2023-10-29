#ifndef MUTEN_TENSOR_HPP
#define MUTEN_TENSOR_HPP

#include <memory>
#include <numeric>
#include <vector>

#include "backend/backend.hpp"
namespace muten {

template <typename T>
class Tensor {
 public:
  Tensor(const std::shared_ptr<Backend>& backend, const std::vector<int>& sizes)
      : _sizes(sizes),
        _strides(_sizes),
        _size(
            std::reduce(_sizes.begin(), _sizes.end(), 0, std::multiplies<T>{})),

        _data(nullptr),
        _backend(backend) {
    std::size_t bytes = _size * sizeof(T);
    T* raw_data = static_cast<T*>(_backend->allocate(bytes));
    auto deleter = [b = this->_backend](T* ptr) {
      b->free(static_cast<void*>(ptr));
    };
    _data = std::shared_ptr<T>(raw_data, deleter);
  }

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
  std::shared_ptr<Backend> _backend;
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
Tensor<T> zeros(std::shared_ptr<Backend>& backend,
                const std::vector<int>& sizes) {
  auto tensor = Tensor<T>(backend, sizes);
  const std::size_t num_bytes = sizeof(T) * tensor.num_elements();
  backend->memset(tensor.data(), 0, num_bytes);

  return tensor;
}

};  // namespace tensor
};  // namespace muten

#endif
