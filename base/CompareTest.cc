#include <array>
#include <ctime>
#include <iostream>
#include <vector>

#include "Array.h"
#include "Vector.h"
#include "gtest/gtest.h"
TEST(CompareTest, test1) {
  clock_t startTime, endTime;
  pcl::EfficientArray<int> ar1(100000);
  startTime = clock();
  for (int i = 0; i < 99000; i++) {
    ar1[i] = i + 1;
  }
  endTime = clock();
  std::cout << "the array run time is = " << endTime - startTime << std::endl;
  clock_t startTime1, endTime1;

  std::array<int, 100000> ar2;
  startTime1 = clock();
  for (int i = 0; i < 99000; i++) {
    ar2[i] = i + 1;
  }
  endTime1 = clock();
  std::cout << "the STL array run time is = " << endTime1 - startTime1
            << std::endl;

  clock_t startTime2, endTime2;
  pcl::EfficientVector<int> ar3;
  startTime2 = clock();
  for (int i = 0; i < 99000; i++) {
    ar3.push_back(i + 2);
  }
  endTime2 = clock();
  std::cout << "the vector run time is = " << endTime2 - startTime2
            << std::endl;

  clock_t startTime3, endTime3;
  std::vector<int> ar4;
  startTime3 = clock();
  for (int i = 0; i < 99000; i++) {
    ar4.push_back(i + 2);
  }
  endTime3 = clock();
  std::cout << "the STL vector run time is = " << endTime3 - startTime3
            << std::endl;
}
