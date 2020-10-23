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

  using Base::at;
  using Base::back;
  using Base::Base;
  using Base::begin;
  using Base::capacity;
  using Base::data;
  using Base::empty;
  using Base::end;
  using Base::front;
  using Base::insert;
  using Base::pop_back;
  using Base::push_back;
  using Base::resize;         // Resizes the vector to contain `n` elements.
  using Base::shrink_to_fit;  // Reduces memory usage by freeing unused memory
  using Base::size;
  using Base::swap;  // Swaps the contents of the Vector with the other
                     // Vector,for exampla:vector1.swap(vector2)

  /**
   * @brief Returns true if the vector contains an occurrence of value;
   *  otherwise returns false.
   *
   * @param value
   * @return true
   * @return false
   */
  bool contains(const T& value) {
    const_iterator b = this->begin();
    const_iterator e = this->end();
    return std::find(b, e, value) != e;
  }
  /**
   * @brief Returns the number of occurrences of value in the vector.
   *
   * @param value
   * @return int
   */
  int count(const T& value) {
    const_iterator b = this->begin();
    const_iterator e = this->end();
    return static_cast<int>((std::count(b, e, value)));
  }
  /**
   * @brief Returns the index positon of the begin occurrence of the value valu
   * in the vector,searching forward from index position start.
   *
   * @param value
   * @param start
   * @return int
   */
  int indexOf(const T& value, size_t start) {
    size_t size = this->size();
    if (start < 0) start = std::max((size_t)0, start + size);
    if (start < size) {
      const_iterator n = this->begin() + start - 1;
      const_iterator e = this->end();
      while (++n != e) {
        if (*n == value) return n - this->begin();
      }
    }
    return -1;
  }
  /**
   * @brief Returns the index position of the end occurrence of value in the
   * vector, searching backward from index position start.
   *
   * @param value
   * @param start
   * @return int
   */
  int endIndexOf(const T& value, int start) {
    size_t size = this->size();
    if (start < 0)
      start += size;
    else if (start >= size)
      start = size - 1;
    if (start > 0) {
      const_iterator b = this->begin();
      const_iterator n = this->begin() + start + 1;
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
    const_iterator from = this->begin() + pos;
    const_iterator to = this->begin() + pos + len;
    for (from; from != to; ++from) {
      midVector->push_back(*from);
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
    push_back(value);
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

    for (EfficientVector<T>::const_iterator it1 = val1.begin();
         it1 != val1.end(); it1++) {
      ret_val->push_back(*it1);
    }
    for (EfficientVector<T>::const_iterator it2 = val2.begin();
         it2 != val2.end(); it2++) {
      ret_val->push_back(*it2);
    }
    return *ret_val;
  }
  /**
   * @brief Returns the vector val1 followed by all the items in the vector
   * val2.
   *
   * @param val1
   * @param val2
   */
  // friend void operator+(EfficientList<T>& val1, EfficientList<T>& val2) {
  //   for (EfficientList<T>::iterator it1 = val2.begin(); it1 != val2.end();
  //        it1++) {
  //     val1.push_back(*it1);
  //   }
  // }
  const_reference operator[](size_t i) const { return data()[i]; }
  reference operator[](size_t i) { return data()[i]; }
};

}  // namespace pcl
