#include "muten/backend/cpu.hpp"

#include <cstdlib>
#include <cstring>

using namespace muten;

void *backend::Cpu::allocate(std::size_t n) noexcept { return std::malloc(n); }
void backend::Cpu::free(void *mem) noexcept { std::free(mem); }
void backend::Cpu::memset(void *mem, int c, std::size_t n) noexcept {
  std::memset(mem, c, n);
}
void backend::Cpu::memcpy(void *dest, void *src, std::size_t n) noexcept {
  std::memcpy(dest, src, n);
}
