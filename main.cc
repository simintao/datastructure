#include <iostream>
#include "base/include/HMap.h"
#include "base/include/Map.h"

using pcl::HMap;
using pcl::Map;

int main() {
  HMap<int, const char *> hmap{{1, "a"}, {1, "b"}};
  for (auto p = hmap.cbegin(); p != hmap.cend(); p++) {
    std::cout << p->first << " " << p->second << std::endl;
  }

  Map<int, const char *> bmap{{1, "a"}, {1, "b"}};
  for (auto p = bmap.cbegin(); p != bmap.cend(); p++) {
    std::cout << p->first << " " << p->second << std::endl;
  }
}