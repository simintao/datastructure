/**
 * @file Map.hh
 * @author simin tao (taosm@pcl.ac.cn)
 * @brief The map container for the eda project.
 * @version 0.1
 * @date 2020-10-09
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include <functional>
#include <utility>

#include "absl/container/btree_map.h"

namespace pcl {

/**
 * @brief Add convenience functions around abseil container.
 *
 * @tparam KEY
 * @tparam VALUE
 * @tparam CMP
 */
template <class KEY, class VALUE, class CMP = std::less<KEY>>
class Map : public absl::btree_map<KEY, VALUE, CMP> {
 public:
  using Base = typename Map::btree_map;

  Map() : absl::btree_map<KEY, VALUE, CMP>() {}
  using Base::Base;
  explicit Map(const CMP& cmp) : absl::btree_map<KEY, VALUE, CMP>(cmp) {}

  using iterator = typename Base::iterator;
  using citerator = typename Base::const_iterator;

  using Base::begin;
  using Base::cbegin;
  using Base::cend;
  using Base::clear;
  using Base::emplace;
  using Base::empty;
  using Base::end;
  using Base::erase;
  using Base::insert;
  using Base::size;

  template <typename... Args>
  iterator emplaceHint(const citerator hint, Args... args) {
    return emplace_hint(hint, std::forward<Args>(args)...);
  }

  inline VALUE& first() {
    assert(!empty());
    return *begin();
  }

  inline const VALUE& first() const {
    assert(!empty());
    return *cbegin();
  }

  inline const KEY& firstKey() const {
    assert(!empty());
    return cbegin().key();
  }

  inline VALUE& last() {
    assert(!empty());
    return *(end() - 1);
  }

  inline VALUE& last() const {
    assert(!empty());
    return *(cend() - 1);
  }

  inline const KEY& lastKey() const {
    assert(!empty());
    return *(cend() - 1).key();
  }
  /**
   * @brief Find out if key is in the map.
   *
   * @param key
   * @return true if find out.
   * @return false
   */
  bool hasKey(const KEY key) const { return this->find(key) != this->end(); }

  // Find the value corresponding to key.
  VALUE
  findKey(const KEY key) const {
    auto find_iter = this->find(key);
    if (find_iter != this->end())
      return find_iter->second;
    else
      return nullptr;
  }
  void findKey(const KEY key,
               // Return Values.
               VALUE& value, bool& exists) const {
    auto find_iter = this->find(key);
    if (find_iter != this->end()) {
      value = find_iter->second;
      exists = true;
    } else
      exists = false;
  }
  void findKey(const KEY& key,
               // Return Values.
               KEY& map_key, VALUE& value, bool& exists) const {
    auto find_iter = this->find(key);
    if (find_iter != this->end()) {
      map_key = find_iter->first;
      value = find_iter->second;
      exists = true;
    } else
      exists = false;
  }

  void insert(const KEY& key, VALUE value) { this->operator[](key) = value; }

  void deleteContents() {
    Iterator iter(this);
    while (iter.hasNext()) delete iter.next();
  }

  void deleteArrayContents() {
    Iterator iter(this);
    while (iter.hasNext()) delete[] iter.next();
  }

  void deleteContentsClear() {
    deleteContents();
    Map<KEY, VALUE, CMP>::clear();
  }

  /**
   * @brief Java style container itererator.
   *
   * Map::Iterator<string *, Value, stringLess> iter(map);
   * while (iter.hasNext()) {
   *   Value *v = iter.next();
   * }
   *
   */
  class Iterator {
   public:
    Iterator() {}
    explicit Iterator(Map<KEY, VALUE, CMP>* container) {
      if (container != nullptr) _iter = container->begin();
    }
    explicit Iterator(const Map<KEY, VALUE, CMP>& container) {
      if (container != nullptr) _iter = container->begin();
    }
    void init(Map<KEY, VALUE, CMP>* container) {
      container = container;
      if (container != nullptr) _iter = container->begin();
    }
    void init(const Map<KEY, VALUE, CMP>& container) {
      if (container != nullptr) _iter = container->begin();
    }
    bool hasNext() { return _iter != _container->end(); }
    VALUE next() { return _iter++->second; }
    void next(KEY* key, VALUE* value) {
      *key = _iter->first;
      *value = _iter->second;
      _iter++;
    }

   private:
    Map<KEY, VALUE, CMP>* _container;
    typename Map<KEY, VALUE, CMP>::iterator _iter;
  };
  friend class Iterator;

  class ConstIterator {
   public:
    ConstIterator() {}
    explicit ConstIterator(const Map<KEY, VALUE, CMP>* container) {
      if (container != nullptr) _iter = container->begin();
    }
    explicit ConstIterator(const Map<KEY, VALUE, CMP>& container) {
      if (container != nullptr) _iter = container->begin();
    }
    void init(const Map<KEY, VALUE, CMP>* container) {
      if (container != nullptr) _iter = container->begin();
    }
    void init(const Map<KEY, VALUE, CMP>& container) {
      if (container != nullptr) _iter = container->begin();
    }
    bool hasNext() {
      return _container != nullptr && _iter != _container->end();
    }
    VALUE next() { return _iter++->second; }
    void next(KEY* key, VALUE* value) {
      *key = _iter->first;
      *value = _iter->second;
      _iter++;
    }

    inline const KEY& key() const { return _iter->first(); }
    inline const VALUE& value() const { return _iter->second(); }
    inline const VALUE& operator*() const { return _iter->value(); }
    inline const VALUE* operator->() const { return &(_iter->value()); }
    inline bool operator==(const ConstIterator& o) const {
      return _iter == o._iter;
    }
    inline bool operator!=(const ConstIterator& o) const {
      return _iter != o._iter;
    }

   private:
    Map<KEY, VALUE, CMP>* _container;
    typename Map<KEY, VALUE, CMP>::citerator _iter;
  };

  friend class ConstIterator;

  class KeyIterator {
   public:
    KeyIterator() = default;
    explicit KeyIterator(ConstIterator o) : i(o) {}

    const KEY& operator*() const { return i.key(); }
    const KEY* operator->() const { return &i.key(); }
    bool operator==(KeyIterator o) const { return i == o.i; }
    bool operator!=(KeyIterator o) const { return i != o.i; }

   private:
    ConstIterator i;
  };

  friend class KeyIterator;
};

}  // namespace pcl
