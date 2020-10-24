#include <iostream>

#include "Array.h"
#include "gtest/gtest.h"
TEST(ArrayTest, base) {
  pcl::EfficientArray<int> ea(5);
  for (int i = 0; i < 3; i++) {
    ea[i] = i + 2;
  }
  for (pcl::EfficientArray<int>::const_iterator it = ea.begin(); it != ea.end();
       ++it) {
    std::cout << *it << std::endl;
  }

  int size = ea.size();
  bool empty = ea.empty();
  std::cout << size << " " << empty << std::endl;
  int &front = ea.front();
  int &back = ea.back();
  const int *begin = ea.begin();
  const int *end = ea.end();

  std::cout << front << " " << back << std::endl;
  std::cout << *begin << " " << *end << std::endl;

  ea.fill(6);
  for (pcl::EfficientArray<int>::const_iterator it = ea.begin(); it != ea.end();
       ++it) {
    std::cout << *it << std::endl;
  }
}
TEST(ArrayTest, operator) {
  pcl::EfficientArray<int> ea1(5);
  pcl::EfficientArray<int> ea2(5);

  for (int i = 0; i < 5; i++) {
    ea1[i] = i + 2;
    ea2[i] = i + 2;
  }
  for (pcl::EfficientArray<int>::const_iterator it = ea1.begin();
       it != ea1.end(); ++it) {
    std::cout << *it << std::endl;
  }
  bool isEqual = (ea1 == ea2) ? true : false;
  bool nEqual = (ea1 != ea2) ? true : false;
  std::cout << isEqual << std::endl;
  std::cout << nEqual << std::endl;
  int size = ea1.size();
  bool empty = ea1.empty();
  std::cout << size << " " << empty << std::endl;
  ea1.fill(6);
  for (pcl::EfficientArray<int>::const_iterator it = ea1.begin();
       it != ea1.end(); ++it) {
    std::cout << *it << std::endl;
  }
}