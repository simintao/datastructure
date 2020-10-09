// Copyright (c) 2020, Pcl.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "absl/container/btree_map.h"

namespace pcl {    

// Add convenience functions around abseil container.
template <class KEY, class VALUE, class CMP = std::less<KEY>>
class Map : public absl::btree_map<KEY, VALUE, CMP> {
public:
  using Base = typename Map::btree_map;

  Map() : absl::btree_map<KEY, VALUE, CMP>() {}
  using Base::Base;
  explicit Map(const CMP &cmp) : absl::btree_map<KEY, VALUE, CMP>(cmp) {}

  // Find out if key is in the map.
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
               VALUE &value, bool &exists) const {
    auto find_iter = this->find(key);
    if (find_iter != this->end()) {
      value = find_iter->second;
      exists = true;
    } else
      exists = false;
  }
  void findKey(const KEY &key,
               // Return Values.
               KEY &map_key, VALUE &value, bool &exists) const {
    auto find_iter = this->find(key);
    if (find_iter != this->end()) {
      map_key = find_iter->first;
      value = find_iter->second;
      exists = true;
    } else
      exists = false;
  }

  void insert(const KEY &key, VALUE value) { this->operator[](key) = value; }

  void deleteContents() {
    Iterator iter(this);
    while (iter.hasNext())
      delete iter.next();
  }

  void deleteArrayContents() {
    Iterator iter(this);
    while (iter.hasNext())
      delete[] iter.next();
  }

  void deleteContentsClear() {
    deleteContents();
    Map<KEY, VALUE, CMP>::clear();
  }

  // Java style container itererator
  //  Map::Iterator<string *, Value, stringLess> iter(map);
  //  while (iter.hasNext()) {
  //    Value *v = iter.next();
  //  }
  class Iterator {
  public:
    Iterator() : _container(nullptr) {}
    explicit Iterator(Map<KEY, VALUE, CMP> *container)
        : _container(container) {
      if (_container != nullptr)
        _iter = _container->begin();
    }
    explicit Iterator(Map<KEY, VALUE, CMP> &container)
        : _container(&container) {
      if (_container != nullptr)
        _iter = _container->begin();
    }
    void init(Map<KEY, VALUE, CMP> *container) {
      _container = container;
      if (_container != nullptr)
        _iter = _container->begin();
    }
    void init(Map<KEY, VALUE, CMP> &container) {
      _container = &container;
      if (_container != nullptr)
        _iter = _container->begin();
    }
    bool hasNext() {
      return _container != nullptr && _iter != _container->end();
    }
    VALUE next() { return _iter++->second; }
    void next(KEY &key, VALUE &value) {
      key = _iter->first;
      value = _iter->second;
      _iter++;
    }
    Map<KEY, VALUE, CMP> *container() { return _container; }

  private:
    Map<KEY, VALUE, CMP> *_container;
    typename Map<KEY, VALUE, CMP>::iterator _iter;
  };

  class ConstIterator {
  public:
    ConstIterator() : _container(nullptr) {}
    explicit ConstIterator(const Map<KEY, VALUE, CMP> *container)
        : _container(container) {
      if (_container != nullptr)
        _iter = _container->begin();
    }
    explicit ConstIterator(const Map<KEY, VALUE, CMP> &container)
        : _container(&container) {
      if (_container != nullptr)
        _iter = _container->begin();
    }
    void init(const Map<KEY, VALUE, CMP> *container) {
      _container = container;
      if (_container != nullptr)
        _iter = _container->begin();
    }
    void init(const Map<KEY, VALUE, CMP> &container) {
      _container = &container;
      if (_container != nullptr)
        _iter = _container->begin();
    }
    bool hasNext() {
      return _container != nullptr && _iter != _container->end();
    }
    VALUE next() { return _iter++->second; }
    void next(KEY &key, VALUE &value) {
      key = _iter->first;
      value = _iter->second;
      _iter++;
    }
    const Map<KEY, VALUE, CMP> *container() { return _container; }

  private:
    const Map<KEY, VALUE, CMP> *_container;
    typename Map<KEY, VALUE, CMP>::const_iterator _iter;
  };
};

} // namespace pcl