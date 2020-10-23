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
  using const_iterator = typename Base::const_iterator;

  /*constructor and destructor*/
  using Base::Base;
  using Base::operator=;
  ~Map() = default;

  /*accessor*/
  using Base::at;
  using Base::operator[];

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

  /*modifier*/
  using Base::clear;
  using Base::emplace;
  using Base::emplace_hint;
  using Base::erase;
  using Base::extract;
  using Base::insert;
  using Base::insert_or_assign;
  using Base::merge;
  using Base::swap;
  using Base::try_emplace;

  /*lookup*/
  using Base::contains;
  using Base::count;
  using Base::equal_range;
  using Base::find;
  using Base::lower_bound;
  using Base::upper_bound;

  /*observers*/
  using Base::key_comp;
  using Base::value_comp;

  template <typename K, typename V, typename C>
  friend bool operator==(const Map<K, V, C>&, const Map<K, V, C>&);
  template <typename K, typename V, typename C>
  friend bool operator<(const Map<K, V, C>&, const Map<K, V, C>&);

  inline VALUE& first() {
    assert(!empty());
    return begin()->second;
  }

  inline const VALUE& first() const {
    assert(!empty());
    return cbegin()->second;
  }

  inline const KEY& firstKey() const {
    assert(!empty());
    return cbegin()->first;
  }

  inline VALUE& last() {
    assert(!empty());
    return (--end())->second;
  }

  inline const VALUE& last() const {
    assert(!empty());
    return (--cend())->second;
  }

  inline const KEY& lastKey() const {
    assert(!empty());
    return (--cend())->first;
  }

  /**
   * @brief Get all map keys.
   *
   * @return std::list<KEY> all map keys.
   */
  std::list<KEY> keys() const {
    std::list<KEY> ret_value;
    for (auto p : *this) {
      ret_value.push_back(p->first);
    }
    return ret_value;
  }

  /**
   * @brief Get all map values.
   *
   * @return std::list<VALUE> all map values.
   */
  std::list<VALUE> values() const {
    std::list<VALUE> ret_value;
    for (auto p : *this) {
      ret_value.push_back(p->second);
    }
    return ret_value;
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
    if (find_iter != this->end()) {
      return find_iter->second;
    } else {
      return default_value;
    }
  }

  void insert(const KEY& key, const VALUE& value) {
    this->operator[](key) = value;
  }

  void deleteContents() {
    Iterator iter(this);
    while (iter.hasNext()) {
      delete iter.next();
    }
  }

  void deleteArrayContents() {
    Iterator iter(this);
    while (iter.hasNext()) {
      delete[] iter.next();
    }
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
    typename Map<KEY, VALUE, CMP>::const_iterator _iter;
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
    typename Map<KEY, VALUE, CMP>::const_iterator _iter;
  };

  friend class KeyIterator;
};

template <typename KEY, typename VALUE, typename CMP>
inline bool operator==(const Map<KEY, VALUE, CMP>& lhs,
                       const Map<KEY, VALUE, CMP>& rhs) {
  const typename Map<KEY, CMP>::Base& lhs_base = lhs;
  const typename Map<KEY, CMP>::Base& rhs_base = rhs;
  return lhs_base == rhs_base;
}

template <typename KEY, typename VALUE, typename CMP>
inline bool operator<(const Map<KEY, VALUE, CMP>& lhs,
                      const Map<KEY, VALUE, CMP>& rhs) {
  const typename Map<KEY, CMP>::Base& lhs_base = lhs;
  const typename Map<KEY, CMP>::Base& rhs_base = rhs;
  return lhs_base < rhs_base;
}

template <typename KEY, typename VALUE, typename CMP>
inline bool operator!=(const Map<KEY, VALUE, CMP>& lhs,
                       const Map<KEY, VALUE, CMP>& rhs) {
  const typename Map<KEY, CMP>::Base& lhs_base = lhs;
  const typename Map<KEY, CMP>::Base& rhs_base = rhs;
  return !(lhs_base == rhs_base);
}

template <typename KEY, typename VALUE, typename CMP>
inline bool operator<=(const Map<KEY, VALUE, CMP>& lhs,
                       const Map<KEY, VALUE, CMP>& rhs) {
  return !(rhs < lhs);
}

template <typename KEY, typename VALUE, typename CMP>
inline bool operator>=(const Map<KEY, VALUE, CMP>& lhs,
                       const Map<KEY, VALUE, CMP>& rhs) {
  return !(lhs < rhs);
}

template <typename KEY, typename VALUE, typename CMP>
inline bool operator>(const Map<KEY, VALUE, CMP>& lhs,
                      const Map<KEY, VALUE, CMP>& rhs) {
  return rhs < lhs;
}

template <typename KEY, typename VALUE, typename CMP>
inline void swap(Map<KEY, VALUE, CMP>& lhs, Map<KEY, VALUE, CMP>& rhs) {
  lhs.swap(rhs);
}

/**
 * @brief The multimap is an ordered associative container.
 *
 * It allows multiple elements with equivalent keys.
 */
template <typename KEY, typename VALUE, typename CMP = std::less<KEY>>
class Multimap : public absl::btree_multimap<KEY, VALUE, CMP> {
  using Base = typename Multimap::btree_multimap;
  using iterator = typename Base::iterator;
  using const_iterator = typename Base::const_iterator;
  using ValueType = typename Base::value_type;

 public:
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
  using Base::insert;
  using Base::lower_bound;
  using Base::merge;
  using Base::rbegin;
  using Base::rend;
  using Base::size;
  using Base::swap;
  using Base::upper_bound;
  using Base::operator=;

  template <typename K, typename V, typename C>
  friend bool operator==(const Multimap<K, V, C>&, const Multimap<K, V, C>&);

  template <typename K, typename V, typename C>
  friend bool operator<(const Multimap<K, V, C>&, const Multimap<K, V, C>&);

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
    typename Multimap<KEY, VALUE, CMP>::const_iterator _iter;
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
    typename Multimap<KEY, VALUE, CMP>::const_iterator _iter;
  };

  friend class KeyIterator;
};

template <typename KEY, typename VALUE, typename CMP>
inline bool operator==(const Multimap<KEY, VALUE, CMP>& lhs,
                       const Multimap<KEY, VALUE, CMP>& rhs) {
  const typename Multimap<KEY, CMP>::Base& lhs_base = lhs;
  const typename Multimap<KEY, CMP>::Base& rhs_base = rhs;
  return lhs_base == rhs_base;
}

template <typename KEY, typename VALUE, typename CMP>
inline bool operator<(const Multimap<KEY, VALUE, CMP>& lhs,
                      const Multimap<KEY, VALUE, CMP>& rhs) {
  const typename Multimap<KEY, CMP>::Base& lhs_base = lhs;
  const typename Multimap<KEY, CMP>::Base& rhs_base = rhs;
  return lhs_base < rhs_base;
}

template <typename KEY, typename VALUE, typename CMP>
inline bool operator!=(const Multimap<KEY, VALUE, CMP>& lhs,
                       const Multimap<KEY, VALUE, CMP>& rhs) {
  return !(lhs == rhs);
}

template <typename KEY, typename VALUE, typename CMP>
inline bool operator<=(const Multimap<KEY, VALUE, CMP>& lhs,
                       const Multimap<KEY, VALUE, CMP>& rhs) {
  return !(rhs < lhs);
}

template <typename KEY, typename VALUE, typename CMP>
inline bool operator>=(const Multimap<KEY, VALUE, CMP>& lhs,
                       const Multimap<KEY, VALUE, CMP>& rhs) {
  return !(lhs < rhs);
}

template <typename KEY, typename VALUE, typename CMP>
inline bool operator>(const Multimap<KEY, VALUE, CMP>& lhs,
                      const Multimap<KEY, VALUE, CMP>& rhs) {
  return rhs < lhs;
}

template <typename KEY, typename VALUE, typename CMP>
inline void swap(Multimap<KEY, VALUE, CMP>& lhs,
                 Multimap<KEY, VALUE, CMP>& rhs) {
  lhs.swap(rhs);
}

}  // namespace pcl
