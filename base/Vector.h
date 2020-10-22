/**
 * @file Vector.h
 * @author Lh
 * @brief The Vector container for the eda project.
 * @version 0.1
 * @date 2020-10-20
 *
 * @copyright Copyright (c) 2020
 *
 */
#pragma once
#include <algorithm>

#include "absl/container/inlined_vector.h"

namespace pcl {
template <typename T>
class EfficientVector : public absl::InlinedVector<T, /* N= */ 256> {
 public:
  using Base = typename EfficientVector::InlinedVector;
  using iterator = typename Base::iterator;
  using const_iterator = typename Base::const_iterator;
  using pointer = typename Base::pointer;
  using const_pointer = typename Base::const_pointer;
  using reference = typename Base::reference;
  using const_reference = typename Base::const_reference;

  using Base::Base;
  using Base::operator=;

  bool isEmpty() { return this->empty(); }
  void pushBack(const T& v) { this->push_back(v); }
  void pushBack(T&& v) { this->push_back(v); }
  void popBack() { this->pop_back(); }
  void grow(size_t n) { this->resize(n); }
  size_t getSize() const { return this->size(); }
  size_t getCapacity() const { return this->capacity(); }
  pointer getData() { return this->data(); }
  const_pointer getData() const { return this->data(); }
  reference elementAt(size_t i) { return this->at(i); }
  const_reference elementAt(size_t i) const { return this->at(i); }
  reference getFront() { return this->front(); }
  const_reference getFront() const { return this->front(); }
  reference getBack() { return this->back(); }
  const_reference getBack() const { return this->back(); }
  iterator first() { return this->begin(); }
  const_iterator first() const { return this->begin(); }
  iterator last() { return this->end(); }
  const_iterator last() const { return this->end(); }
  /**
   * @brief Returns true if the vector contains an occurrence of value;
   *  otherwise returns false.
   *
   * @param value
   * @return true
   * @return false
   */
  bool contains(const T& value) {
    const_iterator b = this->first();
    const_iterator e = this->last();
    return std::find(b, e, value) != e;
  }
  /**
   * @brief Returns the number of occurrences of value in the vector.
   *
   * @param value
   * @return int
   */
  int count(const T& value) {
    const_iterator b = this->first();
    const_iterator e = this->end();
    return static_cast<int>((std::count(b, e, value)));
  }
  /**
   * @brief Returns the index positon of the first occurrence of the value valu
   * in the vector,searching forward from index position start.
   *
   * @param value
   * @param start
   * @return int
   */
  int indexOf(const T& value, size_t start) {
    size_t size = this->getSize();
    if (start < 0) start = std::max((size_t)0, start + size);
    if (start < size) {
      const_iterator n = this->first() + start - 1;
      const_iterator e = this->last();
      while (++n != e) {
        if (*n == value) return n - this->first();
      }
    }
    return -1;
  }
  /**
   * @brief Returns the index position of the last occurrence of value in the
   * vector, searching backward from index position start.
   *
   * @param value
   * @param start
   * @return int
   */
  int lastIndexOf(const T& value, int start) {
    size_t size = this->getSize();
    if (start < 0)
      start += size;
    else if (start >= size)
      start = size - 1;
    if (start > 0) {
      const_iterator b = this->first();
      const_iterator n = this->first() + start + 1;
      while (n != b) {
        if (*--n == value) return n - b;
      }
    }
    return -1;
  }
  /**
   * @brief Returns a vector whose elements are copied from this vectro,starting
   * at position pos, len elements are copied.
   *
   * @param pos
   * @param len
   * @return EfficientVector<T>&
   */
  EfficientVector<T>& mid(size_t pos, size_t len) {
    EfficientVector<T>* midVector = new EfficientVector<T>();
    const_iterator from = this->first() + pos;
    const_iterator to = this->first() + pos + len;
    for (from; from != to; ++from) {
      midVector->pushBack(*from);
    }

    return *midVector;
  }
  /**
   * @brief Appends value to the vector.
   *
   * @param value
   * @return EfficientVector<T>&
   */
  EfficientVector<T>& operator+=(const T& value) {
    pushBack(value);
    return *this;
  }
  /**
   * @brief Returns a vector that contains all the items in vector val1
   * followed by all the items in the vector val2.
   *
   * @param val1
   * @param val2
   * @return EfficientVector<T>&
   */
  friend EfficientVector<T>& operator+(const EfficientVector<T>& val1,
                                       const EfficientVector<T>& val2) {
    EfficientVector<T>* ret_val = new EfficientVector<T>;

    for (EfficientVector<T>::const_iterator it1 = val1.first();
         it1 != val1.last(); it1++) {
      ret_val->pushBack(*it1);
    }
    for (EfficientVector<T>::const_iterator it2 = val2.first();
         it2 != val2.last(); it2++) {
      ret_val->pushBack(*it2);
    }
    return *ret_val;
  }
 
};

}  // namespace pcl
