#include <iostream>
#include "gtest/gtest.h"

#include "Vector.h"
//
TEST(VectorTest, Push){
  pcl::EfficientVector<int, 5> ev;
  ev.pushBack(1);
  ev.pushBack(2);
  ev.pushBack(3);
  for (pcl::EfficientVector<int, 5>::iterator it = ev.first(); it != ev.last();
       ++it) {
    std::cout << *it << std::endl;
  }
}