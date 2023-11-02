
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <cstddef>

#include "muten/cpu_allocator.hpp"
#include "muten/device.hpp"
#include "muten/tensor.hpp"

using namespace muten;

// #define TENSOR_TYPES int32_t, int64_t, float, double
#define TENSOR_TYPES int32_t

std::vector<int> stride_from_dim(const std::vector<int>& dim) {
  std::vector<int> strides(dim.size());
  strides[0] = 1;
  for (int i = 1; i < strides.size(); i++) {
    strides[i] = strides[i - 1] * dim[i - 1];
  }
  return strides;
}

TEMPLATE_TEST_CASE("Tensor", "[tensor]", TENSOR_TYPES) {
  Device dev = {.type = DeviceType::CPU, .index = 0};
  using v = std::vector<int>;
  auto dim = GENERATE(v{1, 2, 3}, v{1}, v{10, 10, 10, 8, 7, 2},
                      v{256, 256, 256, 256});
  auto t = Tensor<TestType>(dev, dim);

  SECTION("data accessor") { REQUIRE(t.data() != nullptr); }
  SECTION("dim accessor") { REQUIRE(t.dim() == dim); }
  SECTION("num elements accessor") {
    std::size_t mul = 1;
    for (const auto& val : dim) mul *= val;
    REQUIRE(t.num_elements() == mul);
  }
  SECTION("stride accessor") { REQUIRE(t.strides() == stride_from_dim(dim)); }
  SECTION("begin operator") { REQUIRE(begin(t) == t.data()); }
  SECTION("end operator") { REQUIRE(end(t) == t.data() + t.num_elements()); }
}
