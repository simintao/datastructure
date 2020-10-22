#include <iostream>

#include "Array.h"
#include "gtest/gtest.h"
TEST(ArrayTest, base) {
  pcl::EfficientArray<int> ea(5);
  for (int i = 0; i < 3; i++) {
    ea[i] = i + 2;
  }
  for (pcl::EfficientArray<int>::const_iterator it = ea.first();
       it != ea.last(); ++it) {
    std::cout << *it << std::endl;
  }

  int size = ea.getSize();
  bool empty = ea.isEmpty();
  std::cout << size << " " << empty << std::endl;
  int &front = ea.getFront();
  int &back = ea.getBack();
  const int *first = ea.first();
  const int *last = ea.last();
  std::cout << front << " " << back << std::endl;
  std::cout << *first << " " << *last << std::endl;
  ea.allFill(6);
  for (pcl::EfficientArray<int>::const_iterator it = ea.first();
       it != ea.last(); ++it) {
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
  for (pcl::EfficientArray<int>::const_iterator it = ea1.first();
       it != ea1.last(); ++it) {
    std::cout << *it << std::endl;
  }
  bool isEqual = (ea1 == ea2) ? true : false;
  bool nEqual = (ea1 != ea2) ? true : false;
  std::cout << isEqual << std::endl;
  std::cout << nEqual << std::endl;
  int size = ea1.getSize();
  bool empty = ea1.isEmpty();
  std::cout << size << " " << empty << std::endl;
  ea1.allFill(6);
  for (pcl::EfficientArray<int>::const_iterator it = ea1.first();
       it != ea1.last(); ++it) {
    std::cout << *it << std::endl;
  }
}