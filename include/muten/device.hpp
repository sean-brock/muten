#ifndef MUTEN_DEVICE_HPP
#define MUTEN_DEVICE_HPP

#include "device_type.hpp"

namespace muten {
struct Device {
  DeviceType type;
  int index;
};
};  // namespace muten

#endif
