/**
 * @file List.h
 * @author Lh
 * @brief
 * @version 0.1
 * @date 2020-10-20
 *
 * @copyright Copyright (c) 2020
 *
 */
#pragma once
#include <algorithm>
#include <list>

#include "absl/algorithm/algorithm.h"
namespace pcl {
template <typename T>
class EfficientList : public std::list<T> {
 public:
  using Base = typename EfficientList::list;
  using Base::Base;
  using iterator = typename Base::iterator;
  using const_iterator = typename Base::const_iterator;
  using Base::assign;
  using Base::back;   // Returns a reference to the last item in the list.
  using Base::begin;  // Returns an STL-style iterator pointing to the first
                      // item in the list
  using Base::cbegin;
  using Base::cend;
  using Base::clear;  // Removes all items from the list
  using Base::empty;  // returns true if the list is empty
  using Base::end;    // Returns an STL-style iterator pointing to the imaginary
                      // item after the last item in the list
  using Base::erase;  // Removes the item associated with the iterator pos from
                      // the list, and returns an iterator to the next item in
                      // the list
  using Base::front;  // Returns a reference to the first item in the list
  using Base::insert;  // Inserts value at index position i in the list
  using Base::max_size;
  using Base::merge;  // Merges  elements of the two lists in ascending order
  using Base::pop_back;
  using Base::pop_front;
  using Base::push_back;
  using Base::push_front;
  using Base::rbegin;
  using Base::rend;
  using Base::resize;
  using Base::splice;  // Splices the other list at the pos(iterator pointing)
                       // position
  using Base::swap;    // Swaps list other with this list.
  using Base::unique;  // Removes adjacent duplicate elements

  EfficientList<T>& operator+=(const T& value) {
    push_back(value);
    return *this;
  }
  /**
   * @brief Returns a List that contains all the items in List val1
   * followed by all the items in the List val2.
   *
   * @param val1
   * @param val2
   * @return EfficientList<T>&
   */
  friend EfficientList<T>& operator+(const EfficientList<T>& val1,
                                     const EfficientList<T>& val2) {
    EfficientList<T>* ret_val = new EfficientList<T>;

    for (EfficientList<T>::const_iterator it1 = val1.begin(); it1 != val1.end();
         it1++) {
      ret_val->push_back(*it1);
    }
    for (EfficientList<T>::const_iterator it2 = val2.begin(); it2 != val2.end();
         it2++) {
      ret_val->push_back(*it2);
    }
    return *ret_val;
  }
  /**
   * @brief Returns the vectorList val1 followed by all the items in the List
   * val2.
   *
   * @param val1
   * @param val2
   */
  // friend void operator+(EfficientList<T>& val1, EfficientList<T>& val2) {
  //   for (EfficientList<T>::iterator it1 = val2.begin(); it1 != val2.end();
  //        it1++) {
  //     val1.push_back(*it1);
  //   }
  // }

  friend bool operator==(const EfficientList& lhs, const EfficientList& rhs) {
    return absl::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
  }

  friend bool operator!=(const EfficientList& lhs, const EfficientList& rhs) {
    return !(lhs == rhs);
  }

  friend bool operator<(const EfficientList& lhs, const EfficientList& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                        rhs.end());
  }

  friend bool operator>(const EfficientList& lhs, const EfficientList& rhs) {
    return rhs < lhs;
  }

  friend bool operator<=(const EfficientList& lhs, const EfficientList& rhs) {
    return !(rhs < lhs);
  }

  friend bool operator>=(const EfficientList& lhs, const EfficientList& rhs) {
    return !(lhs < rhs);
  }
};
}  // namespace pcl