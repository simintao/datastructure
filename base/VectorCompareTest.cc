#include <ctime>
//#include <vector>
#include <iostream>

#include "Vector.h"
#include "gtest/gtest.h"
TEST(VectorCompare, add) {
  clock_t startTime, endTime;
  pcl::EfficientVector<int> ar;
  startTime = clock();
  for (int i = 0; i < 9900; i++) {
    ar.push_back(i + 2);
  }
  endTime = clock();
  std::cout << "the vector run time is = " << endTime - startTime << std::endl;
}
