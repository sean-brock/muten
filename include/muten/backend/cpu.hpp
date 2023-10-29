#ifndef MUTEN_BACKEND_CPU_HPP
#define MUTEN_BACKEND_CPU_HPP

#include <cstddef>

#include "backend.hpp"
namespace muten {
namespace backend {
class Cpu : public Backend {
 public:
  Cpu() : Backend(0) {}
  void *allocate(std::size_t n) noexcept override;
  void free(void *mem) noexcept override;
  void memset(void *mem, int c, std::size_t n) noexcept override;
  void memcpy(void *dest, void *src, std::size_t n) noexcept override;
};
};  // namespace backend
};  // namespace muten
#endif
