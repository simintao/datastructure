#include <ctime>
#include <iostream>
#include <vector>
//#include "Vector.h"
#include "gtest/gtest.h"

TEST(vectorCompare, addSTL) {
  clock_t startTime, endTime;

  std::vector<int> ar;
  startTime = clock();
  for (int i = 0; i < 9900; i++) {
    ar.push_back(i + 2);
  }
  endTime = clock();
  std::cout << "the STL vector run time is = " << endTime - startTime
            << std::endl;
}
