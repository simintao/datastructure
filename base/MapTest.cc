#include "Map.h"
#include "gtest/gtest-death-test.h"
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
  Map<int, const char *> bmap;
  ASSERT_THROW(bmap.at(1), std::out_of_range);
}

TEST(MapTest, begin) {
  Map<int, const char *> bmap{{1, "a"}, {2, "b"}};
  EXPECT_STREQ(bmap.begin()->second, "a");
}

TEST(MapTest, cbegin) {
  Map<int, const char *> bmap{{1, "a"}, {2, "b"}};
  EXPECT_STREQ(bmap.cbegin()->second, "a");
}

TEST(MapTest, end) {
  Map<int, const char *> bmap{{1, "a"}, {2, "b"}};
  EXPECT_TRUE(bmap.find(3) == bmap.end());
}

TEST(MapTest, cend) {
  Map<int, const char *> bmap{{1, "a"}, {2, "b"}};
  EXPECT_TRUE(bmap.find(3) == bmap.cend());
}

TEST(MapTest, rbegin) {
  Map<int, const char *> bmap{{1, "a"}, {2, "b"}};
  EXPECT_STREQ(bmap.rbegin()->second, "b");
}

TEST(MapTest, rend) {
  Map<int, const char *> bmap{{1, "a"}, {2, "b"}};
  for (auto p = bmap.rbegin(); p != bmap.rend(); p++) {
    std::cout << p->first << " " << p->second << std::endl;
  }
}

TEST(MapTest, crend) {
  Map<int, const char *> bmap{{1, "a"}, {1, "b"}};
  for (auto p = bmap.crbegin(); p != bmap.crend(); p++) {
    std::cout << p->first << " " << p->second << std::endl;
  }
}

TEST(MapTest, emplace) {
  Map<std::string, std::string> m;

  // uses pair's move constructor
  m.emplace(std::make_pair(std::string("a"), std::string("a")));

  // uses pair's converting move constructor
  m.emplace(std::make_pair("b", "abcd"));

  // uses pair's template constructor
  m.emplace("d", "ddd");

  // uses pair's piecewise constructor
  m.emplace(std::piecewise_construct, std::forward_as_tuple("c"),
            std::forward_as_tuple(10, 'c'));
  // as of C++17, m.try_emplace("c", 10, 'c'); can be used

  for (const auto &p : m) {
    std::cout << p.first << " => " << p.second << '\n';
  }
}

TEST(MapTest, emplace_hint) {
  Map<std::string, std::string> m;
  auto hint = m.begin();

  // uses pair's move constructor
  m.emplace_hint(hint, std::make_pair(std::string("a"), std::string("a")));

  // uses pair's converting move constructor
  m.emplace_hint(hint, std::make_pair("b", "abcd"));

  // uses pair's template constructor
  m.emplace_hint(hint, "d", "ddd");

  // uses pair's piecewise constructor
  m.emplace_hint(hint, std::piecewise_construct, std::forward_as_tuple("c"),
                 std::forward_as_tuple(10, 'c'));
  // as of C++17, m.try_emplace("c", 10, 'c'); can be used

  for (const auto &p : m) {
    std::cout << p.first << " => " << p.second << '\n';
  }
}

TEST(MapTest, empty) {
  Map<std::string, std::string> m;
  EXPECT_TRUE(m.empty());
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
