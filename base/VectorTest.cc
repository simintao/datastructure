#include <iostream>

#include "Vector.h"
#include "gtest/gtest.h"
//
TEST(VectorTest, Push) {
  pcl::EfficientVector<int> ev;
  ev.pushBack(1);
  ev.pushBack(2);
  ev.pushBack(3);
  for (pcl::EfficientVector<int>::citerator it = ev.first(); it != ev.last();
       ++it) {
    std::cout << *it << std::endl;
  }
}