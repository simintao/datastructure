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
#include <list>
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
  using iterator = typename Base::iterator;
  using citerator = typename Base::const_iterator;

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
  using Base::erase;
  using Base::extract;
  using Base::find;
  using Base::insert;
  using Base::merge;
  using Base::rbegin;
  using Base::rend;
  using Base::size;
  using Base::swap;

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
  const VALUE value(const KEY key, const VALUE& default_value = VALUE()) const {
    auto find_iter = this->find(key);
    if (find_iter != this->end())
      return find_iter->second;
    else
      return default_value;
  }

  void insert(const KEY& key, const VALUE& value) {
    this->operator[](key) = value;
  }

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
    Iterator() = default;
    explicit Iterator(Map<KEY, VALUE, CMP>* container) {
      if (container != nullptr) {
        _container = container;
        _iter = container->begin();
      }
    }
    explicit Iterator(const Map<KEY, VALUE, CMP>& container) {
      if (container != nullptr) {
        _container = container;
        _iter = container->begin();
      }
    }
    void init(Map<KEY, VALUE, CMP>* container) {
      if (container != nullptr) {
        _container = container;
        _iter = container->begin();
      }
    }
    void init(const Map<KEY, VALUE, CMP>& container) {
      if (container != nullptr) {
        _container = container;
        _iter = container->begin();
      }
    }
    bool hasNext() { return _iter != _container->end(); }
    VALUE next() { return _iter++->second; }
    void next(KEY* key, VALUE* value) {
      *key = _iter->first;
      *value = _iter->second;
      _iter++;
    }

    inline const KEY& key() const { return _iter->first(); }
    inline const VALUE& value() const { return _iter->second(); }
    inline const VALUE& operator*() const { return _iter->value(); }
    inline const VALUE& operator->() const { return &_iter->value(); }
    inline bool operator==(const Iterator& o) const { return _iter == o._iter; }
    inline bool operator!=(const Iterator& o) const { return _iter != o._iter; }

   private:
    Map<KEY, VALUE, CMP>* _container = nullptr;
    typename Map<KEY, VALUE, CMP>::iterator _iter;
  };
  friend class Iterator;

  class ConstIterator {
   public:
    ConstIterator() = default;
    explicit ConstIterator(const Map<KEY, VALUE, CMP>* container) {
      if (container != nullptr) {
        _container = container;
        _iter = container->begin();
      }
    }
    explicit ConstIterator(const Map<KEY, VALUE, CMP>& container) {
      if (container != nullptr) {
        _container = container;
        _iter = container->begin();
      }
    }

    void init(const Map<KEY, VALUE, CMP>* container) {
      if (container != nullptr) {
        _container = container;
        _iter = container->begin();
      }
    }
    void init(const Map<KEY, VALUE, CMP>& container) {
      if (container != nullptr) {
        _container = container;
        _iter = container->begin();
      }
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
    inline const VALUE& operator->() const { return &_iter->value(); }
    inline bool operator==(const ConstIterator& o) const {
      return _iter == o._iter;
    }
    inline bool operator!=(const ConstIterator& o) const {
      return _iter != o._iter;
    }

   private:
    Map<KEY, VALUE, CMP>* _container = nullptr;
    typename Map<KEY, VALUE, CMP>::citerator _iter;
  };

  friend class ConstIterator;

  class KeyIterator {
   public:
    KeyIterator() = default;
    explicit KeyIterator(const Map<KEY, VALUE, CMP>* container) {
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
    KEY next() { return _iter++->first; }
    void next(KEY* key, VALUE* value) {
      *key = _iter->first;
      *value = _iter->second;
      _iter++;
    }

    const KEY& operator*() const { return _iter.key(); }
    bool operator==(KeyIterator o) const { return _iter == o.i; }
    bool operator!=(KeyIterator o) const { return _iter != o.i; }

   private:
    Map<KEY, VALUE, CMP>* _container;
    typename Map<KEY, VALUE, CMP>::citerator _iter;
  };

  friend class KeyIterator;
};

/**
 * @brief The multimap is an ordered associative container.
 *
 * It allows multiple elements with equivalent keys.
 */
template <typename KEY, typename VALUE, typename CMP = std::less<KEY>>
class Multimap : public absl::btree_multimap<KEY, VALUE, CMP> {
  using Base = typename Multimap::btree_multimap;
  using iterator = typename Base::iterator;
  using citerator = typename Base::const_iterator;
  using ValueType = typename Base::value_type;

 public:
  using Base::Base;

  using Base::begin;
  using Base::cbegin;
  using Base::cend;
  using Base::clear;
  using Base::contains;
  using Base::count;
  using Base::emplace;
  using Base::empty;
  using Base::end;
  using Base::equal_range;
  using Base::erase;
  using Base::extract;
  using Base::find;
  using Base::insert;
  using Base::merge;
  using Base::rbegin;
  using Base::rend;
  using Base::size;
  using Base::swap;

  void insert(const KEY& key, const VALUE& value) {
    insert(ValueType(key, value));
  }

  std::list<VALUE> values(const KEY& key) {
    auto ret_values = equal_range(key);
    std::list<VALUE> ret_list;
    for (auto i = ret_values.first; i != ret_values.second; ++i) {
      ret_list.push_back(i->second);
    }

    return ret_list;
  }
  class Iterator {
   public:
    Iterator() = default;
    explicit Iterator(Multimap<KEY, VALUE, CMP>* container) {
      if (container != nullptr) _iter = container->begin();
    }
    explicit Iterator(const Multimap<KEY, VALUE, CMP>& container) {
      if (container != nullptr) _iter = container->begin();
    }
    void init(Multimap<KEY, VALUE, CMP>* container) {
      container = container;
      if (container != nullptr) _iter = container->begin();
    }
    void init(const Multimap<KEY, VALUE, CMP>& container) {
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
    Multimap<KEY, VALUE, CMP>* _container;
    typename Multimap<KEY, VALUE, CMP>::iterator _iter;
  };
  friend class Iterator;

  class ConstIterator {
   public:
    ConstIterator() = default;
    explicit ConstIterator(const Multimap<KEY, VALUE, CMP>* container) {
      if (container != nullptr) _iter = container->begin();
    }
    explicit ConstIterator(const Multimap<KEY, VALUE, CMP>& container) {
      if (container != nullptr) _iter = container->begin();
    }
    void init(const Multimap<KEY, VALUE, CMP>* container) {
      if (container != nullptr) _iter = container->begin();
    }
    void init(const Multimap<KEY, VALUE, CMP>& container) {
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
    Multimap<KEY, VALUE, CMP>* _container;
    typename Multimap<KEY, VALUE, CMP>::citerator _iter;
  };
  friend class ConstIterator;

  class KeyIterator {
   public:
    KeyIterator() = default;
    explicit KeyIterator(const Multimap<KEY, VALUE, CMP>* container) {
      if (container != nullptr) _iter = container->begin();
    }

    void init(const Multimap<KEY, VALUE, CMP>* container) {
      if (container != nullptr) _iter = container->begin();
    }
    void init(const Multimap<KEY, VALUE, CMP>& container) {
      if (container != nullptr) _iter = container->begin();
    }

    const KEY& operator*() const { return _iter.key(); }
    const KEY* operator->() const { return &_iter.key(); }
    bool operator==(KeyIterator o) const { return _iter == o.i; }
    bool operator!=(KeyIterator o) const { return _iter != o.i; }

    bool hasNext() {
      return _container != nullptr && _iter != _container->end();
    }
    KEY next() { return _iter++->first; }
    void next(KEY* key, VALUE* value) {
      *key = _iter->first;
      *value = _iter->second;
      _iter++;
    }

   private:
    Multimap<KEY, VALUE, CMP>* _container;
    typename Multimap<KEY, VALUE, CMP>::citerator _iter;
  };

  friend class KeyIterator;
};
}  // namespace pcl
