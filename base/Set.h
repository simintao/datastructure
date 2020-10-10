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

#include "absl/container/btree_set.h"

namespace pcl {

/**
 * @brief Add convenience functions around abseil set container.
 *
 */
template <class KEY, class CMP = std::less<KEY>>
class Set : public absl::btree_set<KEY, CMP> {
 public:
  using Base = typename Set::btree_set;
  using Base::Base;
  Set() : absl::btree_set<KEY, CMP>() {}
  explicit Set(const CMP &cmp) : absl::btree_set<KEY, CMP>(cmp) {}

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
  static bool equal(const absl::btree_set<KEY, CMP> *set1,
                    const absl::btree_set<KEY, CMP> *set2);

  /**
   * @brief Judge the set2 is the subset of the set.
   *
   * @param set2
   * @return true if set2 is a subset of this set.
   * @return false
   */
  bool isSubset(const absl::btree_set<KEY, CMP> *set2);

  void insertSet(const absl::btree_set<KEY, CMP> *set2);

  void deleteContents() {
    Iterator iter(this);
    while (iter.hasNext()) delete iter.next();
  }

  void deleteContentsClear() {
    deleteContents();
    this->clear();
  }

  static bool intersects(absl::btree_set<KEY, CMP> &set1,
                         absl::btree_set<KEY, CMP> &set2);
  static bool intersects(absl::btree_set<KEY, CMP> *set1,
                         absl::btree_set<KEY, CMP> *set2);

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
    Iterator() : _container(nullptr) {}
    explicit Iterator(absl::btree_set<KEY, CMP> *container)
        : _container(container) {
      if (_container != nullptr) _iter = _container->begin();
    }
    explicit Iterator(absl::btree_set<KEY, CMP> &container)
        : _container(&container) {
      if (_container != nullptr) _iter = _container->begin();
    }
    void init(absl::btree_set<KEY, CMP> *container) {
      _container = container;
      if (_container != nullptr) _iter = _container->begin();
    }
    void init(absl::btree_set<KEY, CMP> &container) {
      _container = &container;
      if (_container != nullptr) _iter = _container->begin();
    }
    bool hasNext() {
      return _container != nullptr && _iter != _container->end();
    }
    KEY next() { return *_iter++; }
    absl::btree_set<KEY, CMP> *container() { return _container; }

   private:
    absl::btree_set<KEY, CMP> *_container;
    typename absl::btree_set<KEY, CMP>::iterator _iter;
  };

  class ConstIterator {
   public:
    ConstIterator() : _container(nullptr) {}
    explicit ConstIterator(const absl::btree_set<KEY, CMP> *container)
        : _container(container) {
      if (_container != nullptr) _iter = _container->begin();
    }
    explicit ConstIterator(const absl::btree_set<KEY, CMP> &container)
        : _container(&container) {
      if (_container != nullptr) _iter = _container->begin();
    }
    void init(const absl::btree_set<KEY, CMP> *container) {
      _container = container;
      if (_container != nullptr) _iter = _container->begin();
    }
    void init(const absl::btree_set<KEY, CMP> &container) {
      _container = &container;
      if (_container != nullptr) _iter = _container->begin();
    }

    bool hasNext() {
      return _container != nullptr && _iter != _container->end();
    }
    KEY next() { return *_iter++; }
    const absl::btree_set<KEY, CMP> *container() { return _container; }

   private:
    const absl::btree_set<KEY, CMP> *_container;
    typename absl::btree_set<KEY, CMP>::const_iterator _iter;
  };
};

template <class KEY, class CMP>
bool Set<KEY, CMP>::equal(const absl::btree_set<KEY, CMP> *set1,
                          const absl::btree_set<KEY, CMP> *set2) {
  if ((set1 == nullptr || set1->empty()) && (set2 == nullptr || set2->empty()))
    return true;
  else if (set1 && set2) {
    if (set1->size() == set2->size()) {
      typename Set<KEY, CMP>::ConstIterator iter1(set1);
      typename Set<KEY, CMP>::ConstIterator iter2(set2);
      while (iter1.hasNext() && iter2.hasNext()) {
        if (iter1.next() != iter2.next()) return false;
      }
      return true;
    } else
      return false;
  } else
    return false;
}

template <class KEY, class CMP>
bool Set<KEY, CMP>::isSubset(const absl::btree_set<KEY, CMP> *set2) {
  if (this->empty() && set2->empty())
    return true;
  else {
    typename Set<KEY, CMP>::ConstIterator iter2(set2);
    while (iter2.hasNext()) {
      const KEY key2 = iter2.next();
      if (!hasKey(key2)) return false;
    }
    return true;
  }
}

template <class KEY, class CMP>
bool Set<KEY, CMP>::intersects(absl::btree_set<KEY, CMP> &set1,
                               absl::btree_set<KEY, CMP> &set2) {
  return intersects(&set1, &set2);
}

template <class KEY, class CMP>
bool Set<KEY, CMP>::intersects(absl::btree_set<KEY, CMP> *set1,
                               absl::btree_set<KEY, CMP> *set2) {
  if (set1 && !set1->empty() && set2 && !set2->empty()) {
    const absl::btree_set<KEY, CMP> *small = set1;
    const absl::btree_set<KEY, CMP> *big = set2;
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
        if (*iter1 < *iter2)
          ++iter1;
        else if (*iter2 < *iter1)
          ++iter2;
        else
          return true;
      }
    } else {
      for (/* empty */; iter2 != last2; ++iter2) {
        const KEY key2 = *iter2;
        if (big->find(key2) != last1) return true;
      }
    }
  }
  return false;
}

/**
 * @brief A complicated way to call the base class operator<.
 *
 * @tparam KEY
 * @tparam CMP
 * @param set1
 * @param set2
 * @return true
 * @return false
 */
template <class KEY, class CMP>
bool operator<(const Set<KEY, CMP> &set1, const Set<KEY, CMP> &set2) {
  const absl::btree_set<KEY, CMP> &set1_base = set1;
  const absl::btree_set<KEY, CMP> &set2_base = set2;
  return set1_base < set2_base;
}

template <class KEY, class CMP>
void Set<KEY, CMP>::insertSet(const absl::btree_set<KEY, CMP> *set2) {
  if (set2) this->insert(set2->begin(), set2->end());
}

}  // namespace pcl