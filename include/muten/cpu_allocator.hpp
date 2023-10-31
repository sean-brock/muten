#ifndef MUTEN_CPU_ALLOCATOR_HPP
#define MUTEN_CPU_ALLOCATOR_HPP

#include "allocator.hpp"

namespace muten {

class CpuAllocator : public Allocator {
 public:
  CpuAllocator() = default;
  virtual ~CpuAllocator() = default;

 private:
  void *allocate_impl(int index, std::size_t n) override;
  void free_impl(int index, void *mem) override;
};
};  // namespace muten

#endif
