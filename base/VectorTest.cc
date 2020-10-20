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
<<<<<<< HEAD
}
TEST(VectorTest, Pop) {
  pcl::EfficientVector<int> ev;
  ev.pushBack(1);
  ev.pushBack(2);
  ev.pushBack(3);
  ev.popBack();
  for (pcl::EfficientVector<int>::citerator it = ev.first(); it != ev.last();
       ++it) {
    std::cout << *it << std::endl;
  }
}
TEST(VectorTest, Empty) {
  pcl::EfficientVector<int> ev;
  for (int i = 0; i < 256; ++i) {
    ev.pushBack(i + 2);
  }
  //  ev.pushBack(1);
  // ev.pushBack(2);
  // ev.pushBack(3);
  // ev.popBack();
  bool flag = ev.isEmpty();
  int size = ev.getSize();
  int mSize = ev.maxSize();
  int capacity = ev.getCapacity();
  // reference ref = ev.elementAt(5);
  std::cout << flag << std::endl;
  std::cout << size << std::endl;
  std::cout << mSize << std::endl;
  std::cout << capacity << std::endl;
}
TEST(VectorTest, operator) {
  pcl::EfficientVector<int> ev1;
  pcl::EfficientVector<int> ev2;
  pcl::EfficientVector<int> ev3;
  pcl::EfficientVector<int> &ev11 = ev1;
  pcl::EfficientVector<int> &ev22 = ev2;
  pcl::EfficientVector<int> &ev33 = ev3;
  ev11.pushBack(1);
  ev11.pushBack(2);
  ev11.pushBack(3);
  ev22.pushBack(5);
  ev22.pushBack(6);
  ev22.pushBack(7);
  /* int &&a = 4;
  ev1.pushBack(a); */
  // for (pcl::EfficientVector<int>::citerator it1 = ev1.first();
  //      it1 != ev1.last(); ++it1) {
  //   std::cout << *it1 << std::endl;
  // }
  // for (pcl::EfficientVector<int>::citerator it2 = ev1.first();
  //      it2 != ev1.last(); ++it2) {
  //   std::cout << *it2 << std::endl;
  // }
  ev3 = ev11 + ev22;
  for (pcl::EfficientVector<int>::citerator it3 = ev3.first();
       it3 != ev3.last(); ++it3) {
    std::cout << *it3 << std::endl;
  }
  ev1 += 4;
  for (pcl::EfficientVector<int>::citerator it1 = ev1.first();
       it1 != ev1.last(); ++it1) {
    std::cout << *it1 << std::endl;
  }
}
TEST(VectorTest, index) {
  pcl::EfficientVector<int> ev;
  for (int i = 0; i < 222; ++i) {
    ev.pushBack(i + 2);
  }
  ev.pushBack(1);
  ev.pushBack(2);
  ev.pushBack(3);

  int count = ev.count(2);
  std::cout << count << std::endl;
  int index = ev.indexOf(5, 0);
  int index1 = ev.lastIndexOf(5, 19);
  std::cout << index << std::endl;
  std::cout << index1 << std::endl;
}
TEST(VectorTest, index1) {
  pcl::EfficientVector<int> ev;
  for (int i = 0; i < 222; ++i) {
    ev.pushBack(i + 2);
  }
  ev.pushBack(1);
  ev.pushBack(2);
  ev.pushBack(3);

  pcl::EfficientVector<int> ret = ev.mid(3, 8);
  for (pcl::EfficientVector<int>::citerator it4 = ret.first();
       it4 != ret.last(); ++it4) {
    std::cout << *it4 << std::endl;
  }
}
=======

  ev.isEmpty();
}
>>>>>>> 3126dfa732a8a4d07119baf4b6fb204cc3d3c1fc
