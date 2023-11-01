
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <cstddef>

#include "muten/cpu_allocator.hpp"
#include "muten/device.hpp"
#include "muten/tensor.hpp"

using namespace muten;

// #define TENSOR_TYPES int32_t, int64_t, float, double
#define TENSOR_TYPES int32_t

TEMPLATE_TEST_CASE("Tensor", "[tensor]", TENSOR_TYPES) {
  Device dev = {.type = DeviceType::CPU, .index = 0};
  std::vector<int> dim = {5, 5, 5};
  auto t = Tensor<TestType>(dev, dim);

  SECTION("data accessor") { REQUIRE(t.data() != nullptr); }
  SECTION("dim accessor") { REQUIRE(t.dim() == dim); }
  SECTION("num elements accessor") {
    std::size_t mul = 1;
    for (const auto& val : dim) mul *= val;
    REQUIRE(t.num_elements() == mul);
  }
  SECTION("stride accessor") {
    std::vector<int> strides = {1, 5, 25};
    REQUIRE(t.strides() == strides);
  }
  SECTION("begin operator") { REQUIRE(begin(t) == t.data()); }
  SECTION("end operator") { REQUIRE(end(t) == t.data() + t.num_elements()); }
  SECTION("end operator") {
    std::vector<int> strides = {1, 5, 25};
    REQUIRE(t.strides() == strides);
  }
}
