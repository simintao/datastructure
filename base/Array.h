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

  using Base::Base;

  size_t getSize() { return this->size(); }
  bool isEmpty() { return this->empty(); }
  pointer data() { return this->data(); }
  const_pointer data() const { return this->data(); }
  reference at(size_t i) { return this->at(i); }
  const_reference at(size_t i) const { return this->at(i); }
  reference getFront() { return this->front(); }
  const_reference getFront() const { return this->front(); }
  reference getBack() { return this->back(); }
  const_reference getBack() const { return this->back(); }
  iterator first() { return this->begin(); }
  const_iterator first() const { return this->begin(); }
  iterator last() { return this->end(); }
  const_iterator last() const { return this->end(); }
  void allFill(const T& val) { this->fill(val); }

  
  friend bool operator==(const EfficientArray& lhs, const EfficientArray& rhs) {
    return absl::equal(lhs.first(), lhs.last(), rhs.first(), rhs.last());
  }

  friend bool operator!=(const EfficientArray& lhs, const EfficientArray& rhs) {
    return !(lhs == rhs);
  }

  friend bool operator<(const EfficientArray& lhs, const EfficientArray& rhs) {
    return std::lexicographical_compare(lhs.first(), lhs.last(), rhs.first(),
                                        rhs.last());
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