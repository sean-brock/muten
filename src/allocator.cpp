#include <loguru.hpp>
#include <map>
#include <memory>
#include <muten/allocator.hpp>
#include <muten/cpu_allocator.hpp>
#include <muten/device_type.hpp>

muten::void_ptr muten::Allocator::allocate(int index, std::size_t n) {
  void *data = allocate_impl(index, n);
  return void_ptr{
      data, [this, index](void *mem) -> void { this->free_impl(index, mem); }};
}

namespace {
std::unique_ptr<muten::Allocator> new_device_allocator(
    const muten::DeviceType &device) {
  switch (device) {
    case muten::DeviceType::CPU:
      return std::make_unique<muten::CpuAllocator>();
    default:
      ABORT_F("No allocator type defined for the device type [%s].",
              to_string(device));
  };
}
};  // namespace

muten::Allocator *muten::get_allocator(const muten::DeviceType &device) {
  static std::map<muten::DeviceType, std::unique_ptr<muten::Allocator>>
      allocators;
  if (allocators.count(device) == 0) {
    allocators[device] = new_device_allocator(device);
  }
  return allocators[device].get();
}
