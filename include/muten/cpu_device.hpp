
#ifndef MUTEN_CPU_DEVICE_HPP
#define MUTEN_CPU_DEVICE_HPP

#include "device.hpp"

namespace muten {

class CpuDevice : public Device {
 public:
  explicit CpuDevice() noexcept : Device(DeviceType::CPU, 0) {}
  void* allocate(std::size_t n) override;
  void free(void* mem) override;
};
};  // namespace muten

#endif
