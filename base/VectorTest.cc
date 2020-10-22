#include <iostream>

#include "Vector.h"
#include "gtest/gtest.h"

TEST(VectorTest, Push) {
  pcl::EfficientVector<int> ev;
  ev.pushBack(1);
  ev.pushBack(2);
  ev.pushBack(3);
  for (pcl::EfficientVector<int>::const_iterator it = ev.first();
       it != ev.last(); ++it) {
    std::cout << *it << std::endl;
  }

  int *data = ev.getData();
  const int *data1 = ev.getData();
  int &ele = ev.elementAt(2);
  const int &ele1 = ev.elementAt(2);
  int &front = ev.getFront();
  const int &front1 = ev.getFront();
  int &back = ev.getBack();
  const int &back1 = ev.getBack();

  std::cout << *data << std::endl;
  std::cout << *data1 << std::endl;
  std::cout << ele << std::endl;
  std::cout << ele1 << std::endl;
  std::cout << front << std::endl;
  std::cout << front1 << std::endl;
  std::cout << back << std::endl;
  std::cout << back1 << std::endl;
}

TEST(VectorTest, Pop) {
  pcl::EfficientVector<int> ev;
  ev.pushBack(1);
  ev.pushBack(2);
  ev.pushBack(3);
  ev.popBack();
  for (pcl::EfficientVector<int>::const_iterator it = ev.first();
       it != ev.last(); ++it) {
    std::cout << *it << std::endl;
  }
}
TEST(VectorTest, Empty) {
  pcl::EfficientVector<int> ev;
  for (int i = 0; i < 256; ++i) {
    ev.pushBack(i + 2);
  }
  bool flag = ev.isEmpty();
  int size = ev.getSize();
  int capacity = ev.getCapacity();
  std::cout << flag << std::endl;
  std::cout << size << std::endl;
  std::cout << capacity << std::endl;
}
TEST(VectorTest, operator) {
  pcl::EfficientVector<int> ev1;
  pcl::EfficientVector<int> ev2;
  pcl::EfficientVector<int> ev3;

  ev1.pushBack(1);
  ev1.pushBack(2);
  ev1.pushBack(3);
  ev2.pushBack(5);
  ev2.pushBack(6);
  ev2.pushBack(7);

  ev3 = ev1 + ev2;
  for (pcl::EfficientVector<int>::const_iterator it3 = ev3.first();
       it3 != ev3.last(); ++it3) {
    std::cout << *it3 << std::endl;
  }
  ev1 += 4;
  for (pcl::EfficientVector<int>::const_iterator it1 = ev1.first();
       it1 != ev1.last(); ++it1) {
    std::cout << *it1 << std::endl;
  }
  pcl::EfficientVector<int> ev4;
  ev4.pushBack(1);
  ev4.pushBack(2);
  ev4.pushBack(3);
  bool equ = (ev1 == ev4) ? true : false;
  std::cout << equ << std::endl;
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
  for (pcl::EfficientVector<int>::const_iterator it4 = ret.first();
       it4 != ret.last(); ++it4) {
    std::cout << *it4 << std::endl;
  }
}

TEST(VectorTest, maxNum) {
  pcl::EfficientVector<int> ev;
  for (int i = 0; i < 280; ++i) {
    ev.pushBack(i + 2);
  }

  pcl::EfficientVector<int> ret = ev.mid(270, 8);
  for (pcl::EfficientVector<int>::const_iterator it4 = ret.first();
       it4 != ret.last(); ++it4) {
    std::cout << *it4 << std::endl;
  }
}

