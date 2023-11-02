#ifndef MUTEN_CPU_ALLOCATOR_HPP
#define MUTEN_CPU_ALLOCATOR_HPP

#include <cstdlib>

#include "allocator.hpp"

namespace muten {

class CpuAllocator : public Allocator {
 public:
  CpuAllocator() = default;
  virtual ~CpuAllocator() = default;

 private:
  inline void *allocate_impl(int index, std::size_t n) noexcept override {
    return std::malloc(n);
  }
  void free_impl(int index, void *mem) noexcept override { std::free(mem); }
};
};  // namespace muten

#endif
