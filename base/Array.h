#pragma once
#include <iostream>

namespace pcl {

template <class T>
class Array {
 public:
  Array(int capacity) {
    this->_capacity = capacity;
    this->_size = 0;
    this->address = new T[this->_capacity];
  }

  Array(const Array &arr) {
    this->_capacity = arr._capacity;
    this->_size = arr._size;
    this->address = new T[arr._capacity];
    for (int i = 0; i < this->_size; i++) {
      this->address[i] = arr.address[i];
    }
  }
  Array &operator=(const Array &arr) {
    if (this->address != NULL) {
      delete[] this->address;
      this->address = NULL;
      this->_capacity = 0;
      this->_size = 0;
    }
    this->_capacity = arr._capacity;
    this->_size = arr._size;
    this->address = new T[arr._capacity];
    for (int i = 0; i < this->_size; i++) {
      this->address[i] = arr.address[i];
    }
    return *this;
  }
  void pushBack(const T &val) {
    if (this->_capacity == this->_size) {
      return;
    }
    this->address[this->_size] = val;
    this->_size++;
  }
  void popBack() {
    if (this->_capacity == 0) {
      return;
    }
    this->_size--;
  }
  T &operator[](int index) { return this->address[index]; }
  int getCapacity() { return this->_capacity; }
  int getSize() { return this->_size; }

  ~Array() {
    if (this->address != NULL) {
      delete[] this->address;
      this->address = NULL;
    }
  }

 private:
  T *address;
  int _capacity;
  int _size;
};
}  // namespace pcl