/**
 * @file HSet.hh
 * @author simin tao (taosm@pcl.ac.cn)
 * @brief The hash set container for the eda project.
 * @version 0.1
 * @date 2020-10-09
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include <utility>

#include "absl/container/flat_hash_set.h"

namespace pcl {

/**
 * @brief A wrap hash set container made up of unique keys.
 *
 * The inherited base class is google abseil hash set.
 */
template <class KEY>
class HSet : public absl::flat_hash_set<KEY> {
 public:
  using Base = typename HSet::flat_hash_set;
  using iterator = typename Base::iterator;
  using const_iterator = typename Base::const_iterator;
  using value_type = typename Base::value_type;

  /*constructor*/
  using Base::Base;
  /*destructor*/
  ~HSet() = default;
  using Base::operator=;

  /*iterator*/
  using Base::begin;
  using Base::cbegin;
  using Base::cend;
  using Base::end;

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

  /*bucket interface*/
  using Base::bucket_count;

  /*hash policy*/
  using Base::load_factor;
  using Base::max_load_factor;
  using Base::rehash;
  using Base::reserve;

  /*observers*/
  using Base::get_allocator;
  using Base::hash_function;
  using Base::key_eq;

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
  static bool equal(const HSet<KEY>* set1, const HSet<KEY>* set2);

  /**
   * @brief Judge the set2 is the subset of the set.
   *
   * @param set2
   * @return true if set2 is a subset of this set.
   * @return false
   */
  bool isSubset(const HSet<KEY>* set2);

  void insertSet(const HSet<KEY>* set2);
  static bool intersects(HSet<KEY>* set1, HSet<KEY>* set2);

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

    explicit Iterator(HSet<KEY>* container) {
      if (container != nullptr) {
        _container = container;
        _iter = container->begin();
      }
    }

    void init(HSet<KEY>* container) {
      if (container != nullptr) {
        _container = container;
        _iter = container->begin();
      }
    }

    bool hasNext() {
      return _container != nullptr && _iter != _container->end();
    }
    Iterator& next() {
      ++_iter;
      return *this;
    }
    HSet<KEY>* container() { return _container; }
    inline const KEY& value() const { return *_iter; }
    inline const KEY& operator*() const { return _iter->value(); }
    inline const KEY& operator->() const { return &_iter->value(); }
    inline bool operator==(const Iterator& o) const { return _iter == o._iter; }
    inline bool operator!=(const Iterator& o) const { return _iter != o._iter; }

   private:
    HSet<KEY>* _container = nullptr;
    typename HSet<KEY>::iterator _iter;
  };

  class ConstIterator {
   public:
    ConstIterator() = default;
    ~ConstIterator() = default;

    explicit ConstIterator(const HSet<KEY>* container) : _container(container) {
      if (_container != nullptr) {
        _iter = _container->begin();
      }
    }

    void init(const HSet<KEY>* container) {
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
    const HSet<KEY>* container() { return _container; }
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
    const HSet<KEY>* _container = nullptr;
    typename HSet<KEY>::const_iterator _iter;
  };
};

template <class KEY>
bool HSet<KEY>::equal(const HSet<KEY>* set1, const HSet<KEY>* set2) {
  if ((set1 == nullptr || set1->empty()) &&
      (set2 == nullptr || set2->empty())) {
    return true;
  } else if (set1 && set2) {
    if (set1->size() == set2->size()) {
      typename HSet<KEY>::ConstIterator iter1(set1);
      typename HSet<KEY>::ConstIterator iter2(set2);
      while (iter1.hasNext() && iter2.hasNext()) {
        if (iter1.next() != iter2.next()) {
          return false;
        }
      }
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

template <class KEY>
bool HSet<KEY>::isSubset(const HSet<KEY>* set2) {
  if (this->empty() && set2->empty()) {
    return true;
  } else {
    typename HSet<KEY>::ConstIterator iter2(set2);
    while (iter2.hasNext()) {
      const KEY key2 = iter2.next();
      if (!hasKey(key2)) return false;
    }
    return true;
  }
}

template <class KEY>
bool HSet<KEY>::intersects(HSet<KEY>* set1, HSet<KEY>* set2) {
  if (set1 && !set1->empty() && set2 && !set2->empty()) {
    const HSet<KEY>* small = set1;
    const HSet<KEY>* big = set2;
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

/**
 * @brief A complicated way to call the base class operator<.
 *
 * @tparam KEY
 *
 * @param set1
 * @param set2
 * @return true
 * @return false
 */
template <class KEY>
bool operator<(const HSet<KEY>& set1, const HSet<KEY>& set2) {
  const typename HSet<KEY>::Base& set1_base = set1;
  const typename HSet<KEY>::Base& set2_base = set2;
  return set1_base < set2_base;
}

template <class KEY>
void HSet<KEY>::insertSet(const HSet<KEY>* set2) {
  if (set2) this->insert(set2->begin(), set2->end());
}

template <typename KEY>
inline void swap(HSet<KEY>& x, HSet<KEY>& y) noexcept(noexcept(x.swap(y))) {
  x.swap(y);
}

template <typename KEY>
inline bool operator==(const HSet<KEY>& x, const HSet<KEY>& y) {
  return static_cast<const typename HSet<KEY>::Base&>(x) == y;
}

template <typename KEY>
inline bool operator!=(const HSet<KEY>& x, const HSet<KEY>& y) {
  return !(x == y);
}

/**
 * @brief A hash set of multiple elements with equivalent keys.
 *
 * @tparam KEY Type of key objects.
 */
template <typename KEY>
class HMultiset : public HSet<KEY> {
 public:
  using Base = typename HMultiset::HSet;
  using Base::Base;
};

template <typename KEY>
inline void swap(HMultiset<KEY>& x,
                 HMultiset<KEY>& y) noexcept(noexcept(x.swap(y))) {
  x.swap(y);
}

template <typename KEY>
inline bool operator==(const HMultiset<KEY>& x, const HMultiset<KEY>& y) {
  return static_cast<const typename HMultiset<KEY>::Base&>(x) == y;
}

template <typename KEY>
inline bool operator!=(const HMultiset<KEY>& x, const HMultiset<KEY>& y) {
  return !(x == y);
}

}  // namespace pcl
