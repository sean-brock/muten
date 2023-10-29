
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <memory>

#include "muten/backend/cpu.hpp"
#include "muten/tensor.hpp"

using namespace muten;

TEST_CASE("Tensor", "[main]") {
  constexpr int num_inputs = 32;
  auto cpu = std::make_shared<backend::Cpu>();
  auto t = Tensor<int>(cpu, {1, 2});
  REQUIRE(nullptr != t.data());
}
