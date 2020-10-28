#include <iostream>
#include "base/include/Map.h"

using pcl::Map;
int main() {
  Map<int, const char *> bmap{{1, "a"}, {1, "b"}};
  for (auto p = bmap.crbegin(); p != bmap.crend(); p++) {
    std::cout << p->first << " " << p->second << std::endl;
  }
}