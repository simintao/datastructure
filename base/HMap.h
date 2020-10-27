/**
 * @file HMap.h
 * @author simin tao (taosm@pcl.ac.cn)
 * @brief The hash map container for the eda project.
 * @version 0.1
 * @date 2020-10-09
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include <list>
#include <unordered_map>

#include "absl/container/flat_hash_map.h"
#include "absl/container/node_hash_map.h"

namespace pcl {

/**
 * @brief A hash map made up of unique key.
 *
 * The hash map is a wrapper of flat hash map from google abseil containers.The
 * hash tables are knows as "Swiss tables" and are designed to be replacements
 * for std::unordered_map.They provide several advantages over the stl
 * containers: 1) Provides C++11 support for C++17 mechanisms such as
 * try_emplace(); 2) Support heterogeneous lookup; 3) Allow optimizations for
 * emplace({key, value}) to avoid allocating a pair in most common cases; 4)
 * Support a heterogeneous std::initializer_list to avoid extra copies for
 * construction and insertion; 5) Guarantees an O(1) erase method by returning
 * void instead of an iterator.
 *
 * Guarantees
 * 1) Keys and values are stored inline; 2) Iterators, references, and pointers
 * to elements are invalidated on rehash; 3) Move operation do not invalidate
 * iterators or pointers.
 *
 * Memory Usage
 * The container uses O((sizeof(std::pair<const K, V>) + 1) * bucket_count()),
 * the max load factor is 87.5%, after which the table doubles in size(making
 * load factor go down by 2x).
 *
 * Heterogeneous Lookup
 * Inserting into or looking up an element within an associative container
 * requires a key.In general, containers require the keys to be of a specific
 * type, which can lead to inefficiencies at call sites that need to convert
 * between near-equivalent types(such as std::string and absl::string_view).To
 * avoid this unnecessary work, the Swiss tables provide heterogeneous lookup
 * for conversions to string types, and for conversions to smart pointer
 * types(std::unique_ptr, std::shared_ptr), through the absl::Hash hashing
 * framwork.
 *
 * @tparam KEY
 * @tparam VALUE
 * @tparam CMP
 */
template <class KEY, class VALUE>
class HMap : public absl::flat_hash_map<KEY, VALUE> {
 public:
  using Base = typename HMap::flat_hash_map;
  using iterator = typename Base::iterator;
  using const_iterator = typename Base::const_iterator;
  using value_type = typename Base::value_type;

  /*constructor*/
  using Base::Base;

  /*destrcutor*/
  ~HMap() = default;
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
  using Base::at;
  using Base::operator[];
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

  using Base::hash_function;
  using Base::key_eq;
  /**
   * @brief Get all map keys.
   *
   * @return std::list<KEY> all map keys.
   */
  std::list<KEY> keys() const {
    std::list<KEY> ret_value;
    for (auto p : *this) {
      ret_value.push_back(p.first);
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
      ret_value.push_back(p.second);
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

  /**
   * @brief Find the value corresponding to key.
   *
   * @param key
   * @param default_value the default return value if not found.
   * @return const VALUE return the found value.
   */
  const VALUE value(const KEY key, const VALUE& default_value = VALUE()) const {
    auto find_iter = this->find(key);
    if (find_iter != this->end()) {
      return find_iter->second;
    } else {
      return default_value;
    }
  }

  /**
   * @brief Insert the (key, value) to the map container.
   *
   * @param key
   * @param value
   */
  void insert(const KEY& key, const VALUE& value) {
    this->operator[](key) = value;
  }

  /**
   * @brief Java style container itererator.
   *
   * HMap::Iterator<string *, Value> iter(hmap);
   * while (iter.hasNext()) {
   *   iter.next();
   * }
   *
   */
  class Iterator {
   public:
    Iterator() = default;
    ~Iterator() = default;
    explicit Iterator(HMap<KEY, VALUE>* container) {
      if (container != nullptr) {
        _container = container;
        _iter = container->begin();
      }
    }

    void init(HMap<KEY, VALUE>* container) {
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
    void next(KEY* key, VALUE* value) {
      *key = _iter->first;
      *value = _iter->second;
      _iter++;
    }
    HMap<KEY, VALUE>* container() { return _container; }
    inline const KEY& key() const { return _iter->first; }
    inline const VALUE& value() const { return _iter->second; }
    inline const VALUE& operator*() const { return _iter->value(); }
    inline const VALUE& operator->() const { return &_iter->value(); }
    inline bool operator==(const Iterator& o) const { return _iter == o._iter; }
    inline bool operator!=(const Iterator& o) const { return _iter != o._iter; }

   private:
    HMap<KEY, VALUE>* _container = nullptr;
    typename HMap<KEY, VALUE>::iterator _iter;
  };
  friend class Iterator;

  class ConstIterator {
   public:
    ConstIterator() = default;
    ~ConstIterator() = default;

    explicit ConstIterator(const HMap<KEY, VALUE>* container) {
      if (container != nullptr) {
        _container = container;
        _iter = container->begin();
      }
    }

    void init(const HMap<KEY, VALUE>* container) {
      if (container != nullptr) {
        _container = container;
        _iter = container->begin();
      }
    }

    bool hasNext() {
      return _container != nullptr && _iter != _container->end();
    }
    ConstIterator& next() {
      ++_iter;
      return *this;
    }
    void next(KEY* key, VALUE* value) {
      *key = _iter->first;
      *value = _iter->second;
      _iter++;
    }
    const HMap<KEY, VALUE>* container() { return _container; }
    inline const KEY& key() const { return _iter->first; }
    inline const VALUE& value() const { return _iter->second; }
    inline const VALUE& operator*() const { return _iter->value(); }
    inline const VALUE& operator->() const { return &_iter->value(); }
    inline bool operator==(const ConstIterator& o) const {
      return _iter == o._iter;
    }
    inline bool operator!=(const ConstIterator& o) const {
      return _iter != o._iter;
    }

   private:
    const HMap<KEY, VALUE>* _container = nullptr;
    typename HMap<KEY, VALUE>::const_iterator _iter;
  };
  friend class ConstIterator;
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
 * The HMultimap is a wrapper of std unordered_multimap.So we can add
 * more convenient interface for development.
 *
 * @tparam KEY Type of key objects.
 * @tparam VALUE Type of value objects.
 */
template <class KEY, class VALUE>
class HMultimap : public std::unordered_multimap<KEY, VALUE> {
 public:
  using Base = typename HMultimap::unordered_multimap;
  using iterator = typename Base::iterator;
  using const_iterator = typename Base::const_iterator;
  using value_type = typename Base::value_type;

  /*constructor*/
  using Base::Base;

  /*destrcutor*/
  ~HMultimap() = default;
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

  /*modifier*/
  using Base::clear;
  using Base::emplace;
  using Base::emplace_hint;
  using Base::erase;
  using Base::extract;
  using Base::insert;
  using Base::merge;
  using Base::swap;

  /*lookup*/
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

  using Base::hash_function;
  using Base::key_eq;
  /**
   * @brief Get all map keys.
   *
   * @return std::list<KEY> all map keys.
   */
  std::list<KEY> keys() const {
    std::list<KEY> ret_value;
    for (auto p : *this) {
      ret_value.push_back(p.first);
    }
    return ret_value;
  }

  /**
   * @brief Get all map values.
   *
   * @return std::list<VALUE> all map values of the key.
   */
  std::list<VALUE> values(const KEY& key) {
    auto ret_values = equal_range(key);
    std::list<VALUE> ret_list;
    for (auto i = ret_values.first; i != ret_values.second; ++i) {
      ret_list.push_back(i->second);
    }

    return ret_list;
  }

  /**
   * @brief Find out if key is in the map.
   *
   * @param key
   * @return true if find out.
   * @return false
   */
  bool hasKey(const KEY key) const { return this->find(key) != this->end(); }

  /**
   * @brief Find the value corresponding to key.
   *
   * @param key
   * @param default_value the default return value if not found.
   * @return const VALUE return the found value.
   */
  const VALUE value(const KEY key, const VALUE& default_value = VALUE()) const {
    auto find_iter = this->find(key);
    if (find_iter != this->end()) {
      return find_iter->second;
    } else {
      return default_value;
    }
  }

  /**
   * @brief Insert the (key, value) to the map container.
   *
   * @param key
   * @param value
   */
  void insert(const KEY& key, const VALUE& value) {
    this->operator[](key) = value;
  }

  /**
   * @brief Java style container itererator.
   *
   * HMap::Iterator<string *, Value> iter(hmap);
   * while (iter.hasNext()) {
   *   iter.next();
   * }
   *
   */
  class Iterator {
   public:
    Iterator() = default;
    ~Iterator() = default;
    explicit Iterator(HMultimap<KEY, VALUE>* container) {
      if (container != nullptr) {
        _container = container;
        _iter = container->begin();
      }
    }

    void init(HMultimap<KEY, VALUE>* container) {
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
    void next(KEY* key, VALUE* value) {
      *key = _iter->first;
      *value = _iter->second;
      _iter++;
    }
    HMultimap<KEY, VALUE>* container() { return _container; }
    inline const KEY& key() const { return _iter->first; }
    inline const VALUE& value() const { return _iter->second; }
    inline const VALUE& operator*() const { return _iter->value(); }
    inline const VALUE& operator->() const { return &_iter->value(); }
    inline bool operator==(const Iterator& o) const { return _iter == o._iter; }
    inline bool operator!=(const Iterator& o) const { return _iter != o._iter; }

   private:
    HMultimap<KEY, VALUE>* _container = nullptr;
    typename HMultimap<KEY, VALUE>::iterator _iter;
  };
  friend class Iterator;

  class ConstIterator {
   public:
    ConstIterator() = default;
    ~ConstIterator() = default;

    explicit ConstIterator(const HMultimap<KEY, VALUE>* container) {
      if (container != nullptr) {
        _container = container;
        _iter = container->begin();
      }
    }

    void init(const HMultimap<KEY, VALUE>* container) {
      if (container != nullptr) {
        _container = container;
        _iter = container->begin();
      }
    }

    bool hasNext() {
      return _container != nullptr && _iter != _container->end();
    }
    ConstIterator& next() {
      ++_iter;
      return *this;
    }
    void next(KEY* key, VALUE* value) {
      *key = _iter->first;
      *value = _iter->second;
      _iter++;
    }
    const HMap<KEY, VALUE>* container() { return _container; }
    inline const KEY& key() const { return _iter->first; }
    inline const VALUE& value() const { return _iter->second; }
    inline const VALUE& operator*() const { return _iter->value(); }
    inline const VALUE& operator->() const { return &_iter->value(); }
    inline bool operator==(const ConstIterator& o) const {
      return _iter == o._iter;
    }
    inline bool operator!=(const ConstIterator& o) const {
      return _iter != o._iter;
    }

   private:
    const HMultimap<KEY, VALUE>* _container = nullptr;
    typename HMultimap<KEY, VALUE>::const_iterator _iter;
  };
  friend class ConstIterator;
};

template <typename KEY, typename VALUE>
inline void swap(HMultimap<KEY, VALUE>& x,
                 HMultimap<KEY, VALUE>& y) noexcept(noexcept(x.swap(y))) {
  x.swap(y);
}

template <typename KEY, typename VALUE>
inline bool operator==(const HMultimap<KEY, VALUE>& x,
                       const HMultimap<KEY, VALUE>& y) {
  return static_cast<const typename HMultimap<KEY, VALUE>::Base&>(x) == y;
}

template <typename KEY, typename VALUE>
inline bool operator!=(const HMultimap<KEY, VALUE>& x,
                       const HMultimap<KEY, VALUE>& y) {
  return !(x == y);
}

}  // namespace pcl
