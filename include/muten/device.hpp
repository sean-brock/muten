#ifndef MUTEN_DEVICE_HPP
#define MUTEN_DEVICE_HPP

#include <cstddef>
#include <memory>

namespace muten {

enum class DeviceType {
  CPU,
  HIP,
  HIP_CPU
  // TODO: CUDA
};

class Device {
 public:
  explicit Device(DeviceType type, int index) noexcept
      : _type(type), _index(index) {}
  virtual void* allocate(std::size_t n);
  virtual void free(void* mem);

  inline DeviceType type() const noexcept { return _type; }
  inline int index() const noexcept { return _index; }

 private:
  DeviceType _type;
  int _index;
};
};  // namespace muten

#endif

/*
auto host = CpuDevice();
auto dev = GPUDevice();
// optimize
dev.reserve(sizeof(int) * 2 * 3 * 2);
// Allocates on host memory.
// t1 owns the unique_ptr.
Tensor t1 = tensor.zeros(2,3); // implicit on cpu
t1 = t1.toDevice(dev); // copies to gpu, frees on cpu
// Allocates t1 size on t2, copies data to t2.
Tensor t2 = t1.toDevice(dev);

return t2;

// Tensor t1 scope ends.
// unique_ptr calls deletor
//


*/
