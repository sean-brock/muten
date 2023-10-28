#include <cstdlib>

#include "muten/device.hpp"


template <>
void *muten::allocate<muten::Backend::CPU>(int index, std::size_t n) {
  return std::malloc(n);
}

template <>
void muten::free<muten::Backend::CPU>(int index, void *mem) {
  return std::free(mem);
}
