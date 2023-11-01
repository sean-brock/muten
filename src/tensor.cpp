#include <muten/tensor.hpp>

using namespace muten;

std::vector<int> tensor_util::generate_strides(const std::vector<int> &dim) {
  if (dim.size() == 0) return {0};
  if (dim.size() == 1) return {1};

  std::vector<int> strides(dim.size());
  strides[0] = 1;
  for (int i = 1; i < dim.size(); i++) {
    strides[i] = strides[i - 1] * dim[i - 1];
  }
  return strides;
}