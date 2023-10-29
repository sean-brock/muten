#ifndef MUTEN_BACKEND_HPP
#define MUTEN_BACKEND_HPP

#include <cstdlib>

namespace muten {

class Backend {
 public:
  Backend(int index) : _index(index) {}
  virtual void *allocate(std::size_t n) = 0;
  virtual void free(void *mem) = 0;
  virtual void memset(void *mem, int c, std::size_t n) = 0;
  virtual void memcpy(void *dest, void *src, std::size_t n) = 0;

  inline int index() const { return _index; }

 private:
  const int _index;
};

// Backend specific implementations
#ifdef MUTEN_BACKEND_HIP
#include "muten/devices/hip.hpp"
#endif
#ifdef MUTEN_BACKEND_CUDA
#include "muten/devices/cuda.hpp"
#endif

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


// Create on device
//
*/
