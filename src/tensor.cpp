#include <muten/tensor.hpp>

std::vector<int> muten::tensor_util::generate_strides(
    const std::vector<int>& dim) {
  if (dim.size() == 0) return {0};
  if (dim.size() == 1) return {1};

  std::vector<int> strides(dim.size());
  strides[0] = 1;
  for (int i = 1; i < dim.size(); i++) {
    strides[i] = strides[i - 1] * dim[i - 1];
  }
  return strides;
}

std::size_t muten::tensor_util::num_elements(const std::vector<int>& dim) {
  std::size_t mul = 1;
  for (const auto& val : dim) mul *= val;
  return mul;
}
