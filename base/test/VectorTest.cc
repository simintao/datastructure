#include <iostream>

#include "Vector.h"
#include "gtest/gtest.h"

TEST(VectorTest, Push) {
  pcl::Vector<int> ev;
  ev.push_back(1);
  ev.push_back(2);
  ev.push_back(3);
  for (pcl::Vector<int>::const_iterator it = ev.begin(); it != ev.end(); ++it) {
    std::cout << *it << std::endl;
  }

  int *data = ev.data();
  const int *data1 = ev.data();
  int &ele = ev.at(2);
  const int &ele1 = ev.at(2);
  int &front = ev.front();
  const int &front1 = ev.front();
  int &back = ev.back();
  const int &back1 = ev.back();

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
  pcl::Vector<int> ev;
  ev.push_back(1);
  ev.push_back(2);
  ev.push_back(3);
  ev.pop_back();

  for (pcl::Vector<int>::const_iterator it = ev.begin(); it != ev.end(); ++it) {
    std::cout << *it << std::endl;
  }
  std::cout << "the size = " << ev.size() << std::endl;
  ev.resize(100);
  std::cout << "after resize,the size = " << ev.size() << std::endl;
  ev.shrink_to_fit();
  std::cout << "after resize,the size = " << ev.size() << std::endl;
}
TEST(VectorTest, Empty) {
  pcl::Vector<int> ev;
  for (int i = 0; i < 256; ++i) {
    ev.push_back(i + 2);
  }
  bool flag = ev.empty();
  int size = ev.size();
  int max_size = ev.max_size();
  int capacity = ev.capacity();
  std::cout << flag << std::endl;
  std::cout << "max size = " << max_size << std::endl;
  std::cout << "size = " << size << std::endl;
  std::cout << "capacity = " << capacity << std::endl;
}
TEST(VectorTest, operator) {
  pcl::Vector<int> ev1;
  pcl::Vector<int> ev2;
  pcl::Vector<int> ev3;

  ev1.push_back(1);
  ev1.push_back(2);
  ev1.push_back(3);
  ev2.push_back(5);
  ev2.push_back(6);
  ev2.push_back(7);
  int val = ev2[2];

  bool com1 = ev1 < ev2;
  bool com2 = ev1 > ev2;
  std::cout << com1 << com2 << std::endl;

  ev3 = ev1 + ev2;
  for (pcl::Vector<int>::const_iterator it3 = ev3.begin(); it3 != ev3.end();
       ++it3) {
    std::cout << *it3 << std::endl;
  }
  ev1 += 4;
  for (pcl::Vector<int>::const_iterator it1 = ev1.begin(); it1 != ev1.end();
       ++it1) {
    std::cout << *it1 << std::endl;
  }
  pcl::Vector<int> ev4;
  ev4.push_back(1);
  ev4.push_back(2);
  ev4.push_back(3);
  bool equ = (ev1 == ev4) ? true : false;
  std::cout << equ << std::endl;
  ev1.pop_back();
  ev1.swap(ev2);
  for (pcl::Vector<int>::const_iterator it3 = ev1.begin(); it3 != ev1.end();
       ++it3) {
    std::cout << *it3 << std::endl;
  }
}
TEST(VectorTest, index) {
  pcl::Vector<int> ev;
  for (int i = 0; i < 222; ++i) {
    ev.push_back(i + 2);
  }
  ev.push_back(1);
  ev.push_back(2);
  ev.push_back(3);

  int count = ev.count(2);
  std::cout << count << std::endl;
  int index = ev.indexOf(5, 0);
  int index1 = ev.endIndexOf(5, 19);
  std::cout << index << std::endl;
  std::cout << index1 << std::endl;
}
TEST(VectorTest, index1) {
  pcl::Vector<int> ev;
  for (int i = 0; i < 222; ++i) {
    ev.push_back(i + 2);
  }
  ev.push_back(1);
  ev.push_back(2);
  ev.push_back(3);

  pcl::Vector<int> ret = ev.mid(3, 8);
  for (pcl::Vector<int>::const_iterator it4 = ret.begin(); it4 != ret.end();
       ++it4) {
    std::cout << *it4 << std::endl;
  }
}

TEST(VectorTest, maxNum) {
  pcl::Vector<int> ev;
  for (int i = 0; i < 280; ++i) {
    ev.push_back(i + 2);
  }

  pcl::Vector<int> ret = ev.mid(270, 8);
  for (pcl::Vector<int>::const_iterator it4 = ret.begin(); it4 != ret.end();
       ++it4) {
    std::cout << *it4 << std::endl;
  }
  pcl::Vector<int> ev1;
  for (int i = 0; i < 5; ++i) {
    ev1.push_back(i + 2);
  }
  for (pcl::Vector<int>::reverse_iterator it5 = ev1.rbegin(); it5 != ev1.rend();
       ++it5) {
    std::cout << *it5 << std::endl;
  }
  ev1.assign(5, 666);
  ev1.emplace(ev1.begin(), 555);
  ev1.erase(ev1.begin() + 1);
  for (pcl::Vector<int>::const_reverse_iterator it5 = ev1.crbegin();
       it5 != ev1.crend(); ++it5) {
    std::cout << *it5 << std::endl;
  }
}
