/**
 * @file Array.h
 * @author Lh
 * @brief The Array container for the eda project.
 * @version 0.1
 * @date 2020-10-20
 *
 * @copyright Copyright (c) 2020
 *
 */
#pragma once
#include <algorithm>

#include "absl/container/fixed_array.h"

namespace pcl {
template <typename T>
class EfficientArray : public absl::FixedArray<T, /* N= */ 256> {
 public:
  using Base = typename EfficientArray::FixedArray;
  using pointer = typename Base::pointer;
  using const_pointer = typename Base::const_pointer;
  using reference = typename Base::reference;
  using const_reference = typename Base::const_reference;
  using iterator = typename Base::iterator;
  using const_iterator = typename Base::const_iterator;

  using Base::at;
  using Base::back;
  using Base::Base;
  using Base::begin;
  using Base::cbegin;
  using Base::cend;
  using Base::crbegin;
  using Base::crend;
  using Base::data;
  using Base::empty;
  using Base::end;
  using Base::fill;
  using Base::front;
  using Base::rbegin;
  using Base::rend;
  using Base::size;

  reference operator[](size_t i) { return data()[i]; }

  friend bool operator==(const EfficientArray& lhs, const EfficientArray& rhs) {
    return absl::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
  }

  friend bool operator!=(const EfficientArray& lhs, const EfficientArray& rhs) {
    return !(lhs == rhs);
  }

  friend bool operator<(const EfficientArray& lhs, const EfficientArray& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                        rhs.end());
  }

  friend bool operator>(const EfficientArray& lhs, const EfficientArray& rhs) {
    return rhs < lhs;
  }

  friend bool operator<=(const EfficientArray& lhs, const EfficientArray& rhs) {
    return !(rhs < lhs);
  }

  friend bool operator>=(const EfficientArray& lhs, const EfficientArray& rhs) {
    return !(lhs < rhs);
  }
};

}  // namespace pcl