#include "Map.h"
#include "gtest/gtest.h"

using pcl::Map;
using pcl::Multimap;

namespace {
TEST(MapTest, Ctor) {
  Map<int, const char *> bmap = {{1, "test"}};

  EXPECT_STREQ(bmap.value(1), "test");
}

TEST(MultimapTest, Ctor) {
  Multimap<int, std::string> mmap = {{1, "test"}, {1, "test1"}};

  std::cout << mmap.size() << std::endl;

  mmap.insert(1, "test2");
  std::cout << mmap.size() << std::endl;

  auto values = mmap.values(1);
  for (auto i : values) {
    std::cout << i << '\n';
  }
}

}  // namespace
