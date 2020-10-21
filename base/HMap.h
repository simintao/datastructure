/**
 * @file HMap.hh
 * @author simin tao (taosm@pcl.ac.cn)
 * @brief The hash map container for the eda project.
 * @version 0.1
 * @date 2020-10-09
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once
#include <utility>

#include "absl/container/flat_hash_map.h"

namespace pcl {

/**
 * @brief A hash map of unique key.
 *
 * @tparam KEY
 * @tparam VALUE
 * @tparam CMP
 */
template <class KEY, class VALUE>
class HMap : public absl::flat_hash_map<KEY, VALUE> {
 public:
  using Base = typename HMap::flat_hash_map;

  HMap() : absl::flat_hash_map<KEY, VALUE>() {}

  using Base::Base;

  using Base::at;
  using Base::begin;
  using Base::cbegin;
  using Base::cend;
  using Base::clear;
  using Base::contains;
  using Base::count;
  using Base::emplace;
  using Base::emplace_hint;
  using Base::empty;
  using Base::end;
  using Base::equal_range;
  using Base::erase;
  using Base::extract;
  using Base::find;
  using Base::insert;
  using Base::insert_or_assign;
  using Base::merge;
  using Base::rehash;
  using Base::reserve;
  using Base::size;
  using Base::swap;
  using Base::try_emplace;
  using Base::operator[];
  using Base::bucket_count;
  using Base::get_allocator;
  using Base::hash_function;
  using Base::key_eq;
  using Base::load_factor;
  using Base::max_load_factor;
  using Base::operator=;

  /**
   * @brief Find out if key is in the map.
   *
   * @param key
   * @return true if find out.
   * @return false
   */
  bool hasKey(const KEY key) const { return this->find(key) != this->end(); }

  VALUE value(const KEY key, const VALUE& default_value = VALUE()) const {
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
    HMap<KEY, VALUE>::clear();
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
    Iterator() : _container(nullptr) {}
    explicit Iterator(HMap<KEY, VALUE>* container) : _container(container) {
      if (_container != nullptr) _iter = _container->begin();
    }
    explicit Iterator(const HMap<KEY, VALUE>& container)
        : _container(&container) {
      if (_container != nullptr) _iter = _container->begin();
    }
    void init(HMap<KEY, VALUE>* container) {
      _container = container;
      if (_container != nullptr) _iter = _container->begin();
    }
    void init(const HMap<KEY, VALUE>& container) {
      _container = &container;
      if (_container != nullptr) _iter = _container->begin();
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
    HMap<KEY, VALUE>* container() { return _container; }

   private:
    HMap<KEY, VALUE>* _container;
    typename HMap<KEY, VALUE>::iterator _iter;
  };

  class ConstIterator {
   public:
    ConstIterator() : _container(nullptr) {}
    explicit ConstIterator(const HMap<KEY, VALUE>* container)
        : _container(container) {
      if (_container != nullptr) _iter = _container->begin();
    }
    explicit ConstIterator(const HMap<KEY, VALUE>& container)
        : _container(&container) {
      if (_container != nullptr) _iter = _container->begin();
    }
    void init(const HMap<KEY, VALUE>* container) {
      _container = container;
      if (_container != nullptr) _iter = _container->begin();
    }
    void init(const HMap<KEY, VALUE>& container) {
      _container = &container;
      if (_container != nullptr) _iter = _container->begin();
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
    const HMap<KEY, VALUE>* container() { return _container; }

   private:
    const HMap<KEY, VALUE>* _container;
    typename HMap<KEY, VALUE>::const_iterator _iter;
  };
};

template <typename KEY, typename VALUE>
inline void swap(HMap<KEY, VALUE>& x,
                 HMap<KEY, VALUE>& y) noexcept(noexcept(x.swap(y))) {
  x.swap(y);
}

template <typename KEY, typename VALUE>
inline bool operator==(const HMap<KEY, VALUE>& x, const HMap<KEY, VALUE>& y) {
  return static_cast<const typename HMap<KEY, VALUE>::Base&>(x) == y;
}

template <typename KEY, typename VALUE>
inline bool operator!=(const HMap<KEY, VALUE>& x, const HMap<KEY, VALUE> y) {
  return !(x == y);
}

/**
 * @brief A hash map of multiple elements with equivalent keys.
 *
 * @tparam KEY Type of key objects.
 * @tparam VALUE Type of value objects.
 */
template <class KEY, class VALUE>
class HMultiMap : public HMap<KEY, VALUE> {
 public:
  using Base = typename HMultiMap::HMap;
  using Base::Base;

  using Base::at;
  using Base::begin;
  using Base::cbegin;
  using Base::cend;
  using Base::clear;
  using Base::contains;
  using Base::count;
  using Base::emplace;
  using Base::emplace_hint;
  using Base::empty;
  using Base::end;
  using Base::equal_range;
  using Base::erase;
  using Base::extract;
  using Base::find;
  using Base::insert;
  using Base::insert_or_assign;
  using Base::merge;
  using Base::rehash;
  using Base::reserve;
  using Base::size;
  using Base::swap;
  using Base::try_emplace;
  using Base::operator[];
  using Base::bucket_count;
  using Base::get_allocator;
  using Base::hash_function;
  using Base::key_eq;
  using Base::load_factor;
  using Base::max_load_factor;
  using Base::operator=;
};

template <typename KEY, typename VALUE>
inline void swap(HMultiMap<KEY, VALUE>& x,
                 HMultiMap<KEY, VALUE>& y) noexcept(noexcept(x.swap(y))) {
  x.swap(y);
}

template <typename KEY, typename VALUE>
inline bool operator==(const HMultiMap<KEY, VALUE>& x,
                       const HMultiMap<KEY, VALUE>& y) {
  return static_cast<const typename HMultiMap<KEY, VALUE>::Base&>(x) == y;
}

template <typename KEY, typename VALUE>
inline bool operator!=(const HMultiMap<KEY, VALUE>& x,
                       const HMultiMap<KEY, VALUE>& y) {
  return !(x == y);
}

}  // namespace pcl
