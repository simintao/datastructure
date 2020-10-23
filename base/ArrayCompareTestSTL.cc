#include <array>
#include <cstring>
#include <ctime>
#include <iostream>

//#include "Array.h"
#include "gtest/gtest.h"

TEST(arrayCompare, addSTL) {
  clock_t startTime, endTime;

  std::array<int, 10000> ar;
  startTime = clock();
  for (int i = 0; i < 9900; i++) {
    ar[i] = i + 1;
  }
  endTime = clock();
  std::cout << "the STL array run time is = " << endTime - startTime
            << std::endl;
}
