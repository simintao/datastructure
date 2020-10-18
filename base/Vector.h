#pragma once
#include <algorithm>

#include "absl/container/inlined_vector.h"

namespace pcl {
template <typename T>
class EfficientVector : public absl::InlinedVector<T, /*N=*/256> {
 public:
  using Base = typename EfficientVector::InlinedVector;
  using iterator = typename Base::iterator;
  using citerator = typename Base::const_iterator;
  using pointer = typename Base::pointer;
  using reference = typename Base::reference;

  using Base::Base;

  bool isEmpty() { return this->empty(); }
  void pushBack(T&& v) { this->push_back(v); }
  void popBack() { this->pop_back(); }
  size_t getSize() const { return this->size(); }
  size_t maxSize() const { return this->max_size(); }
  size_t getCapacity() const { return this->capacity(); }
  pointer getData() const { return this->data(); }
  reference elementAt(size_t i) const { return this->at(i); }
  reference getFront() const { return this->front(); }
  reference getBack() const { return this->back(); }
  citerator first() const { return this->begin(); }
  citerator last() const { return this->end(); }
  void grow(size_t n) { this->resize(n); }

  EfficientVector<T>& operator+=(T const& val) {
    pushBack(val);
    return *this;
  }
  friend EfficientVector<T>& operator+(const EfficientVector<T>& val1,
                                       const EfficientVector<T>& val2) {
    for (EfficientVector<T>::iterator it = val2.first(); it != val2.last();
         it++) {
      val1.pushBack(*it);
    }
    return val1;
  }

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
    if (start < 0) start = std::max((size_t)0, start + size);
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
    if (start > 0) {
      iterator b = this->first();
      iterator n = this->first + start + 1;
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
