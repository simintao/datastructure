//#include <array>
#include <ctime>
#include <iostream>
//#include <vector>

#include "Array.h"
//#include "Vector.h"
#include "gtest/gtest.h"
TEST(arrayCompare, add) {
  clock_t startTime, endTime;
  pcl::EfficientArray<int> ar1(10000);
  startTime = clock();
  for (int i = 0; i < 9900; i++) {
    ar1[i] = i + 1;
  }
  endTime = clock();
  std::cout << "the array run time is = " << endTime - startTime << std::endl;
}
