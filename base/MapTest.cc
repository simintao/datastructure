#include "Map.h"
#include "gtest/gtest.h"

using pcl::Map;
using pcl::Multimap;

namespace {
TEST(MapTest, initializer_list) {
  Map<int, const char *> bmap = {{1, "test"}};

  EXPECT_STREQ(bmap.value(1), "test");
}

TEST(MapTest, copy_constructor) {
  Map<int, const char *> bmap = {{1, "test"}};
  Map<int, const char *> bmap1(bmap);

  EXPECT_STREQ(bmap1.value(1), "test");
}

TEST(MapTest, assignmen_operator) {
  Map<int, const char *> bmap = {{1, "test"}};
  Map<int, const char *> bmap1 = bmap;

  EXPECT_STREQ(bmap1.value(1), "test");
}

TEST(MapTest, move_constructor) {
  Map<int, const char *> bmap = {{1, "test"}};
  Map<int, const char *> bmap1(std::move(bmap));

  EXPECT_STREQ(bmap1.value(1), "test");
}

TEST(MapTest, move_assignment) {
  Map<int, const char *> bmap = {{1, "test"}};
  Map<int, const char *> bmap1;
  bmap1 = std::move(bmap);

  EXPECT_STREQ(bmap1.value(1), "test");
}

TEST(MapTest, range_constructor) {
  std::vector<std::pair<int, const char *>> v = {{1, "a"}, {2, "b"}};
  Map<int, const char *> bmap1(v.begin(), v.end());

  EXPECT_STREQ(bmap1.value(1), "a");
}

TEST(MapTest, at) {
  Map<int, const char *> bmap{{1, "a"}, {2, "b"}};
  const char *value = bmap.at(1);

  EXPECT_STREQ(bmap.at(1), "a");
}

TEST(MapTest, at_exception) {
  Map<int, const char *> bmap{{1, "a"}, {2, "b"}};
  const char *value = bmap.at(3);

  EXPECT_STREQ(bmap.at(1), "a");
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
