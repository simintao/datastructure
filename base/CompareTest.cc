#include <array>
#include <ctime>
#include <iostream>
#include <vector>

#include "Array.h"
#include "Vector.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "gtest/gtest.h"
int main() {
  bool flag = true;
  size_t value;
  if (flag == true) {
    absl::Time startTime, endTime;
    startTime = absl::Now();

    constexpr size_t array_size = 900000;
    pcl::Array<size_t, array_size* 2 / 3>* ar1 =
        new pcl::Array<size_t, array_size * 2 / 3>(array_size);
    for (size_t i = 0; i < array_size; i++) {
      (*ar1)[i] = i + 1;
    }
    endTime = absl::Now();
    absl::Duration duration = endTime - startTime;
    int64_t duration_time = duration / absl::Nanoseconds(1);
    std::cout << "the array write time is = " << duration_time << "ns"
              << std::endl;
    startTime = absl::Now();
    for (size_t i = 0; i < array_size; i++) {
      value = (*ar1)[i];
    }
    endTime = absl::Now();
    duration = endTime - startTime;
    duration_time = duration / absl::Nanoseconds(1);
    std::cout << "the array read time is = " << duration_time << "ns"
              << std::endl;
    std::cout << "last parameter is " << value << std::endl;
    absl::Time startTime1, endTime1;

    startTime1 = absl::Now();
    std::array<size_t, array_size>* ar2 = new std::array<size_t, array_size>;
    for (size_t i = 0; i < array_size; i++) {
      (*ar2)[i] = i + 1;
    }
    endTime1 = absl::Now();
    duration = endTime1 - startTime1;
    std::cout << "the STL array write time is = "
              << duration / absl::Nanoseconds(1) << "ns" << std::endl;
    startTime1 = absl::Now();
    for (size_t i = 0; i < array_size; i++) {
      value = (*ar2)[i];
    }
    endTime1 = absl::Now();
    duration = endTime1 - startTime1;
    std::cout << "the STL array read time is = "
              << duration / absl::Nanoseconds(1) << "ns" << std::endl;
    std::cout << "last parameter is " << value << std::endl;
  }

  if (flag == false) {
    size_t value_size = 100000000;
    absl::Time startTime2, endTime2, lastTime2;
    pcl::Vector<size_t> ar3;
    startTime2 = absl::Now();
    for (int i = 0; i < value_size; i++) {
      ar3.push_back(i + 1);
    }
    endTime2 = absl::Now();
    absl::Duration duration = endTime2 - startTime2;
    std::cout << "the vector write time is = "
              << duration / absl::Nanoseconds(1) << "ns" << std::endl;
    startTime2 = absl::Now();
    for (pcl::Vector<size_t>::iterator it2 = ar3.begin(); it2 != ar3.end();
         ++it2) {
      value = *it2;
    }
    endTime2 = absl::Now();
    duration = endTime2 - startTime2;
    std::cout << "the vector read time is = " << duration / absl::Nanoseconds(1)
              << "ns" << std::endl;
    std::cout << "last parameter is " << value << std::endl;
    absl::Time startTime3, endTime3;
    std::vector<size_t> ar4;
    startTime3 = absl::Now();
    for (int i = 0; i < value_size; i++) {
      ar4.push_back(i + 1);
    }
    endTime3 = absl::Now();
    duration = endTime3 - startTime3;
    std::cout << "the STL vector write time is = "
              << duration / absl::Nanoseconds(1) << "ns" << std::endl;
    startTime3 = absl::Now();
    for (std::vector<size_t>::iterator it3 = ar4.begin(); it3 != ar4.end();
         ++it3) {
      value = *it3;
    }
    endTime3 = absl::Now();
    duration = endTime3 - startTime3;
    std::cout << "the STL vector read time is = "
              << duration / absl::Nanoseconds(1) << "ns" << std::endl;
    std::cout << "last parameter is " << value << std::endl;
  }
  return 0;
}
