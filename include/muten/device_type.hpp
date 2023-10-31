#ifndef MUTEN_DEVICE_TYPE_HPP
#define MUTEN_DEVICE_TYPE_HPP

namespace muten {
enum class DeviceType {
#ifdef MUTEN_ENABLE_HIP
  HIP,
#endif
  CPU
};
};  // namespace muten

#endif
