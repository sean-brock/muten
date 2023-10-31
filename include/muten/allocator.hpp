#ifndef MUTEN_ALLOCATOR_HPP
#define MUTEN_ALLOCATOR_HPP

#include <cstddef>
#include <memory>

namespace muten {

enum class DeviceType;

class Allocator {
 public:
  Allocator() = default;
  virtual ~Allocator() = default;

  std::unique_ptr<void> allocate(int index, std::size_t n);

 protected:
  virtual void *allocate_impl(int index, std::size_t n) = 0;
  virtual void free_impl(int index, void *mem) = 0;
};

Allocator *get_allocator(const DeviceType &device);
};  // namespace muten
#endif
