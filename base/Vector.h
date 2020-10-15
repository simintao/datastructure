#pragma once
#include "absl/container/inlined_vector.h"

namespace pcl {
template <typename T, size_t N>
class EfficientVector : public absl::InlinedVector<T, N> {
  using Base = typename EfficientVector::InlinedVector;

 public:
  using Base::Base;

  bool isEmpty() { return empty(); }

  size_t getSize() {}
};

}  // namespace pcl