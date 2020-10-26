/**
 * @file Set.hh
 * @author simin tao (taosm@pcl.ac.cn)
 * @brief The set container for the eda project.
 * @version 0.1
 * @date 2020-10-09
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include <functional>
#include <utility>

#include "absl/container/btree_set.h"

namespace pcl {

/**
 * @brief A wrap set container made up of unique keys.
 *
 * The inherited base class is google abseil btree set.
 */
template <class KEY, class CMP = std::less<KEY>>
class Set : public absl::btree_set<KEY, CMP> {
 public:
  using Base = typename Set::btree_set;

  /*constructor*/
  using Base::Base;
  /*destrcutor*/
  ~Set() = default;
  using Base::operator=;

  /*iterators*/
  using Base::begin;
  using Base::cbegin;
  using Base::cend;
  using Base::crbegin;
  using Base::crend;
  using Base::end;
  using Base::rbegin;
  using Base::rend;

  /*capacity*/
  using Base::empty;
  using Base::max_size;
  using Base::size;

  /*modifiers*/
  using Base::clear;
  using Base::emplace;
  using Base::emplace_hint;
  using Base::erase;
  using Base::extract;
  using Base::insert;
  using Base::merge;
  using Base::swap;

  /*lookup*/
  using Base::contains;
  using Base::count;
  using Base::equal_range;
  using Base::find;
  using Base::lower_bound;
  using Base::upper_bound;

  /*observer*/
  using Base::get_allocator;
  using Base::key_comp;
  using Base::value_comp;

  /**
   * @brief Removes all items from this set that are contained in the other set.
   *
   * Returns a reference to this set.
   */
  Set<KEY, CMP>& subtract(const Set<KEY, CMP>& other) {
    for (const auto& e : other) {
      erase(e);
    }

    return *this;
  }

  inline Set<KEY, CMP>& operator<<(const KEY& value) {
    insert(value);
    return *this;
  }
  inline Set<KEY, CMP>& operator|=(const Set<KEY, CMP>& other) {
    unite(other);
    return *this;
  }
  inline Set<KEY, CMP>& operator|=(const KEY& value) {
    insert(value);
    return *this;
  }
  inline Set<KEY, CMP>& operator&=(const Set<KEY, CMP>& other) {
    intersect(other);
    return *this;
  }
  inline Set<KEY, CMP>& operator&=(const KEY& value) {
    Set<KEY, CMP> result;
    if (contains(value)) result.insert(value);
    return (*this = result);
  }
  inline Set<KEY, CMP>& operator+=(const Set<KEY, CMP>& other) {
    unite(other);
    return *this;
  }
  inline Set<KEY, CMP>& operator+=(const KEY& value) {
    insert(value);
    return *this;
  }
  inline Set<KEY, CMP>& operator-=(const Set<KEY, CMP>& other) {
    subtract(other);
    return *this;
  }
  inline Set<KEY, CMP>& operator-=(const KEY& value) {
    remove(value);
    return *this;
  }
  inline Set<KEY, CMP> operator|(const Set<KEY, CMP>& other) const {
    Set<KEY, CMP> result = *this;
    result |= other;
    return result;
  }
  inline Set<KEY, CMP> operator&(const Set<KEY, CMP>& other) const {
    Set<KEY, CMP> result = *this;
    result &= other;
    return result;
  }
  inline Set<KEY, CMP> operator+(const Set<KEY, CMP>& other) const {
    Set<KEY, CMP> result = *this;
    result += other;
    return result;
  }
  inline Set<KEY, CMP> operator-(const Set<KEY, CMP>& other) const {
    Set<KEY, CMP> result = *this;
    result -= other;
    return result;
  }

  /**
   * @brief Find the entry corresponding to key.
   *
   * @param key
   * @return KEY
   */
  KEY findKey(const KEY key) const {
    auto find_iter = this->find(key);
    if (find_iter != this->end())
      return *find_iter;
    else
      return nullptr;
  }

  /**
   * @brief Find out if key is in the set.
   *
   * @param key
   * @return true when has key.
   * @return false when do not has key.
   */
  bool hasKey(const KEY key) const {
    auto find_iter = this->find(key);
    return find_iter != this->end();
  }

  /**
   * @brief Judge whether the two set is equal.
   *
   * @param set1
   * @param set2
   * @return true when the two set is equal.
   * @return false
   */
  static bool equal(const Set<KEY, CMP>* set1, const Set<KEY, CMP>* set2);

  /**
   * @brief Judge the set2 is the subset of the set.
   *
   * @param set2
   * @return true if set2 is a subset of this set.
   * @return false
   */
  bool isSubset(const Set<KEY, CMP>* set2);
  void insertSet(const Set<KEY, CMP>* set2);

  static bool intersects(Set<KEY, CMP>* set1, Set<KEY, CMP>* set2);

  /**
   * @brief Java style container itererator.
   *
   *  for example:
   *  Set::Iterator<Key*> iter(set);
   *  while (iter.hasNext()) {
   *    Key *v = iter.next();
   *  }
   */
  class Iterator {
   public:
    Iterator() = default;
    ~Iterator() = default;

    explicit Iterator(Set<KEY, CMP>* container) : _container(container) {
      if (_container != nullptr) {
        _iter = _container->begin();
      }
    }

    void init(Set<KEY, CMP>* container) {
      _container = container;
      if (_container != nullptr) {
        _iter = _container->begin();
      }
    }

    bool hasNext() {
      return _container != nullptr && _iter != _container->end();
    }
    Iterator& next() {
      ++_iter;
      return *this;
    }
    Set<KEY, CMP>* container() { return _container; }
    inline const KEY& value() const { return *_iter; }
    inline const KEY& operator*() const { return _iter->value(); }
    inline const KEY& operator->() const { return &_iter->value(); }
    inline bool operator==(const Iterator& o) const { return _iter == o._iter; }
    inline bool operator!=(const Iterator& o) const { return _iter != o._iter; }

   private:
    Set<KEY, CMP>* _container = nullptr;
    typename Set<KEY, CMP>::iterator _iter;
  };

  class ConstIterator {
   public:
    ConstIterator() = default;
    ~ConstIterator() = default;

    explicit ConstIterator(const Set<KEY, CMP>* container)
        : _container(container) {
      if (_container != nullptr) _iter = _container->begin();
    }

    void init(const Set<KEY, CMP>* container) {
      _container = container;
      if (_container != nullptr) {
        _iter = _container->begin();
      }
    }

    bool hasNext() {
      return _container != nullptr && _iter != _container->end();
    }
    ConstIterator& next() {
      ++_iter;
      return *this;
    }
    const Set<KEY, CMP>* container() { return _container; }
    inline const KEY& value() const { return _iter->second; }
    inline const KEY& operator*() const { return _iter->value(); }
    inline const KEY* operator->() const { return &(_iter->value()); }
    inline bool operator==(const ConstIterator& o) const {
      return _iter == o._iter;
    }
    inline bool operator!=(const ConstIterator& o) const {
      return _iter != o._iter;
    }

   private:
    const Set<KEY, CMP>* _container = nullptr;
    typename Set<KEY, CMP>::const_iterator _iter;
  };
};

template <class KEY, class CMP>
bool Set<KEY, CMP>::equal(const Set<KEY, CMP>* set1,
                          const Set<KEY, CMP>* set2) {
  if ((set1 == nullptr || set1->empty()) &&
      (set2 == nullptr || set2->empty())) {
    return true;
  } else if (set1 && set2) {
    if (set1->size() == set2->size()) {
      typename Set<KEY, CMP>::ConstIterator iter1(set1);
      typename Set<KEY, CMP>::ConstIterator iter2(set2);
      while (iter1.hasNext() && iter2.hasNext()) {
        if (iter1.next() != iter2.next()) return false;
      }
      return true;
    } else {
      return false;
    }

  } else {
    return false;
  }
}

template <class KEY, class CMP>
bool Set<KEY, CMP>::isSubset(const Set<KEY, CMP>* set2) {
  if (this->empty() && set2->empty()) {
    return true;
  } else {
    typename Set<KEY, CMP>::ConstIterator iter2(set2);
    while (iter2.hasNext()) {
      const KEY key2 = iter2.next();
      if (!hasKey(key2)) {
        return false;
      }
    }
    return true;
  }
}

template <class KEY, class CMP>
bool Set<KEY, CMP>::intersects(Set<KEY, CMP>* set1, Set<KEY, CMP>* set2) {
  if (set1 && !set1->empty() && set2 && !set2->empty()) {
    const Set<KEY, CMP>* small = set1;
    const Set<KEY, CMP>* big = set2;
    if (small->size() > big->size()) {
      small = set2;
      big = set1;
    }
    auto iter1 = big->begin();
    auto last1 = big->end();
    auto iter2 = small->begin();
    auto last2 = small->end();
    if (static_cast<float>(small->size() + big->size()) <
        (small->size() * log(static_cast<float>(big->size())))) {
      while (iter1 != last1 && iter2 != last2) {
        if (*iter1 < *iter2) {
          ++iter1;
        } else if (*iter2 < *iter1) {
          ++iter2;
        } else {
          return true;
        }
      }
    } else {
      for (/* empty */; iter2 != last2; ++iter2) {
        const KEY key2 = *iter2;
        if (big->find(key2) != last1) {
          return true;
        }
      }
    }
  }
  return false;
}

template <class KEY, class CMP>
void Set<KEY, CMP>::insertSet(const Set<KEY, CMP>* set2) {
  if (set2) {
    this->insert(set2->begin(), set2->end());
  }
}

template <typename KEY, typename CMP>
inline bool operator==(const Set<KEY, CMP>& lhs, const Set<KEY, CMP>& rhs) {
  const typename Set<KEY, CMP>::Base& set1_base = lhs;
  const typename Set<KEY, CMP>::Base& set2_base = rhs;
  return set1_base == set2_base;
}

template <typename KEY, typename CMP>
inline bool operator!=(const Set<KEY, CMP>& lhs, const Set<KEY, CMP>& rhs) {
  const typename Set<KEY, CMP>::Base& set1_base = lhs;
  const typename Set<KEY, CMP>::Base& set2_base = rhs;
  return set1_base != set2_base;
}

template <typename KEY, typename CMP>
inline bool operator<(const Set<KEY, CMP>& lhs, const Set<KEY, CMP>& rhs) {
  const typename Set<KEY, CMP>::Base& set1_base = lhs;
  const typename Set<KEY, CMP>::Base& set2_base = rhs;
  return set1_base < set2_base;
}

template <typename KEY, typename CMP>
inline bool operator<=(const Set<KEY, CMP>& lhs, const Set<KEY, CMP>& rhs) {
  const typename Set<KEY, CMP>::Base& set1_base = lhs;
  const typename Set<KEY, CMP>::Base& set2_base = rhs;
  return set1_base <= set2_base;
}

template <typename KEY, typename CMP>
inline bool operator>=(const Set<KEY, CMP>& lhs, const Set<KEY, CMP>& rhs) {
  const typename Set<KEY, CMP>::Base& set1_base = lhs;
  const typename Set<KEY, CMP>::Base& set2_base = rhs;
  return set1_base >= set2_base;
}

template <typename KEY, typename CMP>
inline bool operator>(const Set<KEY, CMP>& lhs, const Set<KEY, CMP>& rhs) {
  const typename Set<KEY, CMP>::Base& set1_base = lhs;
  const typename Set<KEY, CMP>::Base& set2_base = rhs;
  return set1_base > set2_base;
}

template <typename KEY, typename CMP>
void swap(Set<KEY, CMP>& x, Set<KEY, CMP>& y) {
  return x.swap(y);
}

/**
 * @brief A wrap multi set container.
 *
 */
template <class KEY, class CMP = std::less<KEY>>
class Multiset : public absl::btree_multiset<KEY, CMP> {
 public:
  using Base = typename Multiset::btree_multiset;
  using Base::Base;

  using Base::begin;
  using Base::cbegin;
  using Base::cend;
  using Base::clear;
  using Base::contains;
  using Base::count;
  using Base::crbegin;
  using Base::crend;
  using Base::emplace;
  using Base::emplace_hint;
  using Base::empty;
  using Base::end;
  using Base::equal_range;
  using Base::erase;
  using Base::extract;
  using Base::find;
  using Base::g;
  using Base::insert;
  using Base::key_comp;
  using Base::lower_bound;
  using Base::max_size;
  using Base::merge;
  using Base::rbegin;
  using Base::rend;
  using Base::size;
  using Base::swap;
  using Base::upper_bound;
  using Base::value_comp;
  using Base::operator=;
};

template <typename KEY, typename CMP>
inline bool operator==(const Multiset<KEY, CMP>& lhs,
                       const Multiset<KEY, CMP>& rhs) {
  const typename Multiset<KEY, CMP>::Base& set1_base = lhs;
  const typename Multiset<KEY, CMP>::Base& set2_base = rhs;
  return set1_base == set2_base;
}

template <typename KEY, typename CMP>
inline bool operator!=(const Multiset<KEY, CMP>& lhs,
                       const Multiset<KEY, CMP>& rhs) {
  const typename Multiset<KEY, CMP>::Base& set1_base = lhs;
  const typename Multiset<KEY, CMP>::Base& set2_base = rhs;
  return set1_base != set2_base;
}

template <typename KEY, typename CMP>
inline bool operator<(const Multiset<KEY, CMP>& lhs,
                      const Multiset<KEY, CMP>& rhs) {
  const typename Multiset<KEY, CMP>::Base& set1_base = lhs;
  const typename Multiset<KEY, CMP>::Base& set2_base = rhs;
  return set1_base < set2_base;
}

template <typename KEY, typename CMP>
inline bool operator<=(const Multiset<KEY, CMP>& lhs,
                       const Multiset<KEY, CMP>& rhs) {
  const typename Multiset<KEY, CMP>::Base& set1_base = lhs;
  const typename Multiset<KEY, CMP>::Base& set2_base = rhs;
  return set1_base <= set2_base;
}

template <typename KEY, typename CMP>
inline bool operator>=(const Multiset<KEY, CMP>& lhs,
                       const Multiset<KEY, CMP>& rhs) {
  const typename Multiset<KEY, CMP>::Base& set1_base = lhs;
  const typename Multiset<KEY, CMP>::Base& set2_base = rhs;
  return set1_base >= set2_base;
}

template <typename KEY, typename CMP>
inline bool operator>(const Multiset<KEY, CMP>& lhs,
                      const Multiset<KEY, CMP>& rhs) {
  const typename Multiset<KEY, CMP>::Base& set1_base = lhs;
  const typename Multiset<KEY, CMP>::Base& set2_base = rhs;
  return set1_base > set2_base;
}

template <typename KEY, typename CMP>
void swap(Multiset<KEY, CMP>& x, Multiset<KEY, CMP>& y) {
  return x.swap(y);
}

}  // namespace pcl
