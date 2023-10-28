#ifndef MUTEN_DEVICE_HPP
#define MUTEN_DEVICE_HPP

#include <cstdlib>

namespace muten {

// Backend specific implementations

enum class Backend {
#ifdef MUTEN_BACKEND_HIP
  HIP,
#endif
#ifdef MUTEN_BACKEND_CUDA
  CUDA,
#endif
  CPU
};

#ifdef MUTEN_BACKEND_HIP
#include "muten/devices/hip.hpp"
#endif
#ifdef MUTEN_BACKEND_CUDA
#include "muten/devices/cuda.hpp"
#endif

template <Backend>
void *allocate(int index, std::size_t n);

template <Backend>
void free(int index, void *mem);

template <>
void *allocate<Backend::CPU>(int index, std::size_t n);

template <>
void free<Backend::CPU>(int index, void *mem);
};  // namespace muten
#endif
/*
auto host = CpuBackend();
auto dev = GPUBackend();
// optimize
dev.reserve(sizeof(int) * 2 * 3 * 2);
// Allocates on host memory.
// t1 owns the unique_ptr.
Tensor t1 = tensor.zeros(2,3); // implicit on cpu
t1 = t1.toBackend(dev); // copies to gpu, frees on cpu
// Allocates t1 size on t2, copies data to t2.
Tensor t2 = t1.toBackend(dev);

return t2;

// Tensor t1 scope ends.
// unique_ptr calls deletor
//

dev.createTensor[b]
*/
