#include <algorithm>
#include <functional>
#include <iterator>
#include <random>

#include "Map.h"
#include "gmock/gmock.h"
#include "gtest/gtest-death-test.h"
#include "gtest/gtest.h"

using pcl::Map;
using pcl::Multimap;

using namespace testing;

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
  // emplace would construct the object in place.
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
  // emplace_hint would construct the object in place and insert the object
  // before the hint.
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
  Map<int, std::string> m;

  // auto IsEmpty = [](Map<std::string, std::string> &m) { return m.empty(); };

  EXPECT_THAT(m, IsEmpty());
  // EXPECT_TRUE(m.empty());
}

TEST(MapTest, erase) {
  Map<int, std::string> c = {{1, "one"},  {2, "two"},  {3, "three"},
                             {4, "four"}, {5, "five"}, {6, "six"}};

  // erase all odd numbers from c
  for (auto it = c.begin(); it != c.end();) {
    if (it->first % 2 == 1)
      it = c.erase(it);
    else
      ++it;
  }

  for (auto &p : c) {
    std::cout << p.first << "=>" << p.second << std::endl;
  }

  // use range erase
  c.erase(c.begin(), --c.end());

  for (auto &p : c) {
    std::cout << p.first << "=>" << p.second << std::endl;
  }

  // use erase key
  c.erase(6);

  EXPECT_TRUE(c.empty());
}

TEST(MapTest, extract) {
  Map<int, char> cont{{1, 'a'}, {2, 'b'}, {3, 'c'}};

  auto print = [](std::pair<const int, char> &n) {
    std::cout << " " << n.first << '(' << n.second << ')';
  };

  std::cout << "Start:";
  std::for_each(cont.begin(), cont.end(), print);
  std::cout << '\n';

  // Extract node handle and change key
  auto nh = cont.extract(1);

  std::cout << "After extract and before insert:";
  std::for_each(cont.begin(), cont.end(), print);
  std::cout << '\n';

  // Insert node handle back
  cont.insert(move(nh));
  cont.extract(cont.begin());

  std::cout << "End:";
  std::for_each(cont.begin(), cont.end(), print);
  std::cout << '\n';
}

TEST(MapTest, insert) {
  auto print = [](std::pair<const int, char> &n) {
    std::cout << " " << n.first << '(' << n.second << ')';
  };

  Map<int, char> cont{{1, 'a'}, {2, 'b'}, {3, 'c'}};

  // value type insert
  auto result = cont.insert(std::make_pair(4, 'd'));
  EXPECT_TRUE(result.second);

  // hint insert
  cont.insert(cont.end(), std::make_pair(5, 'e'));
  EXPECT_EQ(cont[5], 'e');

  Map<int, char> cont1{{6, 'f'}};
  // range insert
  cont.insert(cont1.begin(), cont1.end());

  // initializer list insert
  cont.insert({7, 'g'});

  // node type insert
  auto nh = cont.extract(5);
  cont1.insert(move(nh));

  // hint node type insert
  nh = cont.extract(7);
  cont1.insert(cont.begin(), move(nh));

  std::for_each(cont.begin(), cont.end(), print);
  std::cout << '\n';
  std::for_each(cont1.begin(), cont1.end(), print);
}

TEST(MapTest, insert_or_assign) {
  Map<std::string, std::string> myMap;
  myMap.insert_or_assign("a", "apple");
  myMap.insert_or_assign("b", "bannana");
  myMap.insert_or_assign("c", "cherry");
  myMap.insert_or_assign("c", "clementine");

  myMap.insert_or_assign(myMap.begin(), "d", "duck");

  for (const auto &pair : myMap) {
    std::cout << pair.first << " : " << pair.second << '\n';
  }
}

TEST(MapTest, merge) {
  Map<int, std::string> ma{{1, "apple"}, {5, "pear"}, {10, "banana"}};
  Map<int, std::string> mb{
      {2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};
  Map<int, std::string> u;
  u.merge(ma);
  std::cout << "ma.size(): " << ma.size() << '\n';
  u.merge(mb);
  std::cout << "mb.size(): " << mb.size() << '\n';
  std::cout << "mb.at(5): " << mb.at(5) << '\n';
  for (auto const &kv : u) std::cout << kv.first << ", " << kv.second << '\n';
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
