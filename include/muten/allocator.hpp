#ifndef MUTEN_ALLOCATOR_HPP
#define MUTEN_ALLOCATOR_HPP

#include <cstddef>
#include <functional>
#include <memory>

namespace muten {

enum class DeviceType;

using void_ptr = std::unique_ptr<void, std::function<void(void *)>>;

class Allocator {
 public:
  Allocator() = default;
  virtual ~Allocator() = default;
  void_ptr allocate(int index, std::size_t n);

 protected:
  virtual void *allocate_impl(int index, std::size_t n) = 0;
  virtual void free_impl(int index, void *mem) = 0;
};

Allocator *get_allocator(const DeviceType &device);
};  // namespace muten
#endif
