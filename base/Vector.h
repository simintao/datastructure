#pragma once
#include <algorithm>

#include "absl/container/inlined_vector.h"

namespace pcl {
template <typename T>
class EfficientVector : public absl::InlinedVector<T, /*N=*/256> {
  using Base = typename EfficientVector::InlinedVector;
  using pointer = typename Base::pointer;
  using reference = typename Base::reference;
  using iterator = typename Base::iterator;

 public:
  using Base::Base;

  bool isEmpty() { return empty(); }
  void pushBack(T&& v) { this->push_back(v); }
  void popBack() { this->pop_back(); }
  size_t getSize() const { return size(); }
  size_t maxSize() const { return max_size(); }
  size_t getCapacity() const { return capacity(); }
  pointer getData() const { return data(); }
  reference elementAt(size_t i) const { return at(size_t i); }
  reference getFront() const { return front(); }
  reference getBack() const { return back(); }
  iterator first() const { return begin(); }
  iterator last() const { return end(); }
  void grow(size_t n) { this->resize(n); }

  void operator+=(T const& val) {
    pushBack(val);
    return *this;
  }
  // friend EfficientVector<T>& operator+(const EfficientVector<T>& val1,
  //                                      const EfficientVector<T>& val2) {
  //   for (EfficientVector<T>::iterator it = val2.first(); it != val2.last();
  //        it++) {
  //     val1.pushBack(*it);
  //   }
  //   return val1;
  // }

  bool contains(const T& val) {
    iterator b = this->first();
    iterator e = this->last();
    return std::find(b, e, val) != e;
  }

  int count(const T& val) {
    iterator b = this->first();
    iterator e = this->end();
    return static_cast<int>((std::count(b, e, val)));
  }

  int indexOf(const T& val, size_t start) {
    size_t size = this->getSize();
    if (start < 0) start = max(0, start + size);
    if (start < size) {
      iterator n = this->first() + start - 1;
      iterator e = this->last();
      while (++n != e) {
        if (*n == val) return n - this->first();
      }
    }
    return -1;
  }

  int lastIndexOf(const T& val, int start) {
    size_t size = this->getSize();
    if (start < 0)
      start += size;
    else if (start >= size)
      start = size - 1;
    if (from > 0) {
      iterator b = this->first();
      iterator n = this->first + from + 1;
      while (n != b) {
        if (*--n == val) return n - b;
      }
    }
    return -1;
  }

  EfficientVector<T>& mid(size_t pos, size_t len) const {
    EfficientVector<T>* midVector = new EfficientVector<T>();
    iterator from = this->first() + pos;
    iterator to = this->first() + pos + len;
    for (from; from != to; ++from) {
      midVector->pushBack(*from);
    }

    return *midVector;
  }
};

}  // namespace pcl
