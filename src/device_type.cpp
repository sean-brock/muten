#include <loguru.hpp>
#include <muten/device_type.hpp>

const char *muten::to_string(const muten::DeviceType &d) {
  switch (d) {
    case muten::DeviceType::CPU:
      return "CPU";
    default:
      ABORT_F("to_string not implemented for device type [%d]",
              static_cast<int>(d));
  };
}
