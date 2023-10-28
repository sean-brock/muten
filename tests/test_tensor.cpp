
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <memory>

#include "muten/tensor.hpp"

using namespace muten;

TEST_CASE("Tensor", "[main]") {
  constexpr int num_inputs = 32;
  auto t = Tensor<int, Backend::CPU>(0, {1, 2});
  REQUIRE(nullptr != t.data());
}
