#include <algorithm>
#include <functional>
#include <iterator>
#include <random>
#include <unordered_map>

#include "HashMap.h"
#include "gmock/gmock.h"
#include "gtest/gtest-death-test.h"
#include "gtest/gtest.h"

using namespace testing;

using pcl::HashMap;
using pcl::HashMultimap;

namespace {

TEST(HashMapTest, initializer_list) {
  HashMap<int, const char *> hmap = {{1, "test"}};

  EXPECT_STREQ(hmap.value(1), "test");
}

TEST(HashMapTest, copy_constructor) {
  HashMap<int, const char *> hmap = {{1, "test"}};
  HashMap<int, const char *> hmap1(hmap);

  EXPECT_STREQ(hmap1.value(1), "test");
}

TEST(HashMapTest, assignmen_operator) {
  HashMap<int, const char *> hmap = {{1, "test"}};
  HashMap<int, const char *> hmap1 = hmap;

  EXPECT_STREQ(hmap1.value(1), "test");
}

TEST(HashMapTest, move_constructor) {
  HashMap<int, const char *> hmap = {{1, "test"}};
  HashMap<int, const char *> hmap1(std::move(hmap));

  EXPECT_STREQ(hmap1.value(1), "test");
}

TEST(HashMapTest, move_assignment) {
  HashMap<int, const char *> hmap = {{1, "test"}};
  HashMap<int, const char *> hmap1;
  hmap1 = std::move(hmap);

  EXPECT_STREQ(hmap1.value(1), "test");
}

TEST(HashMapTest, range_constructor) {
  std::vector<std::pair<int, const char *>> v = {{1, "a"}, {2, "b"}};
  HashMap<int, const char *> hmap1(v.begin(), v.end());

  EXPECT_STREQ(hmap1.value(1), "a");
}

TEST(HashMapTest, at) {
  HashMap<int, const char *> hmap{{1, "a"}, {2, "b"}};
  const char *value = hmap.at(1);

  EXPECT_STREQ(hmap.at(1), "a");
}

TEST(HashMapTest, at_exception) {
  HashMap<int, const char *> hmap;
  ASSERT_THROW(hmap.at(1), std::out_of_range);
}

TEST(HashMapTest, begin) {
  HashMap<int, const char *> hmap{{1, "a"}, {2, "b"}};
  EXPECT_STREQ(hmap.begin()->second, "a");
}

TEST(HashMapTest, cbegin) {
  HashMap<int, const char *> hmap{{1, "a"}, {2, "b"}};
  EXPECT_STREQ(hmap.cbegin()->second, "a");
}

TEST(HashMapTest, end) {
  HashMap<int, const char *> hmap{{1, "a"}, {2, "b"}};
  EXPECT_TRUE(hmap.find(3) == hmap.end());
}

TEST(HashMapTest, cend) {
  HashMap<int, const char *> hmap{{1, "a"}, {2, "b"}};
  EXPECT_TRUE(hmap.find(3) == hmap.cend());
}

TEST(HashMapTest, emplace) {
  // emplace would construct the object in place.
  HashMap<std::string, std::string> m;

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

TEST(HashMapTest, emplace_hint) {
  // emplace_hint would construct the object in place and insert the object
  // before the hint.
  HashMap<std::string, std::string> m;
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

TEST(HashMapTest, empty) {
  HashMap<int, std::string> m;

  // auto IsEmpty = [](HashMap<std::string, std::string> &m) { return m.empty();
  // };

  EXPECT_THAT(m, IsEmpty());
  // EXPECT_TRUE(m.empty());
}

TEST(HashMapTest, erase) {
  HashMap<int, std::string> c = {{1, "one"},  {2, "two"},  {3, "three"},
                                 {4, "four"}, {5, "five"}, {6, "six"}};

  for (auto &p : c) {
    std::cout << p.first << "=>" << p.second << std::endl;
  }

  // use range erase
  c.erase(c.begin(), c.end());

  for (auto &p : c) {
    std::cout << p.first << "=>" << p.second << std::endl;
  }

  EXPECT_TRUE(c.empty());
}

TEST(HashMapTest, extract) {
  HashMap<int, char> cont{{1, 'a'}, {2, 'b'}, {3, 'c'}};

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

TEST(HashMapTest, insert) {
  auto print = [](std::pair<const int, char> &n) {
    std::cout << " " << n.first << '(' << n.second << ')';
  };

  HashMap<int, char> cont{{1, 'a'}, {2, 'b'}, {3, 'c'}};

  // value type insert
  auto result = cont.insert(std::make_pair(4, 'd'));
  EXPECT_TRUE(result.second);

  // hint insert
  cont.insert(cont.end(), std::make_pair(5, 'e'));
  EXPECT_EQ(cont[5], 'e');

  HashMap<int, char> cont1{{6, 'f'}};
  // range insert
  cont.insert(cont1.begin(), cont1.end());

  // initializer list insert
  cont.insert({7, 'g'});

  // node type insert
  auto nh = cont.extract(5);
  cont1.insert(move(nh));

  // hint node type insert
  nh = cont.extract(7);
  // cont1.insert(cont.cbegin(), move(nh));

  std::for_each(cont.begin(), cont.end(), print);
  std::cout << '\n';
  std::for_each(cont1.begin(), cont1.end(), print);
}

TEST(HashMapTest, insert_or_assign) {
  HashMap<std::string, std::string> myHashMap;
  myHashMap.insert_or_assign("a", "apple");
  myHashMap.insert_or_assign("b", "bannana");
  myHashMap.insert_or_assign("c", "cherry");
  myHashMap.insert_or_assign("c", "clementine");

  myHashMap.insert_or_assign(myHashMap.begin(), "d", "duck");

  for (const auto &pair : myHashMap) {
    std::cout << pair.first << " : " << pair.second << '\n';
  }
}

TEST(HashMapTest, merge) {
  HashMap<int, std::string> ma{{1, "apple"}, {5, "pear"}, {10, "banana"}};
  HashMap<int, std::string> mb{
      {2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};
  HashMap<int, std::string> u;
  u.merge(ma);
  std::cout << "ma.size(): " << ma.size() << '\n';
  u.merge(mb);
  std::cout << "mb.size(): " << mb.size() << '\n';
  std::cout << "mb.at(5): " << mb.at(5) << '\n';
  for (auto const kv : u) std::cout << kv.first << ", " << kv.second << '\n';

  std::cout << std::begin(u)->first;

  auto const &kv1 = std::begin(u);

  std::cout << kv1->first << '\n';
}

// print out a std::pair
template <class Os, class U, class V>
Os &operator<<(Os &os, const std::pair<U, V> &p) {
  return os << p.first << ":" << p.second;
}

// print out a container
template <class Os, class Co>
Os &operator<<(Os &os, const Co &co) {
  os << "{";
  for (auto const &i : co) {
    os << ' ' << i;
  }
  return os << " }\n";
}
TEST(HashMapTest, swap) {
  HashMap<std::string, std::string> m1{
      {"γ", "gamma"},
      {"β", "beta"},
      {"α", "alpha"},
      {"γ", "gamma"},
  },
      m2{{"ε", "epsilon"}, {"δ", "delta"}, {"ε", "epsilon"}};

  const auto &ref = *(m1.begin());
  const auto iter = std::next(m1.cbegin());

  std::cout << "──────── before swap ────────\n"
            << "m1: " << m1 << "m2: " << m2 << "ref: " << ref
            << "\niter: " << *iter << '\n';

  m1.swap(m2);

  std::cout << "──────── after swap ────────\n"
            << "m1: " << m1 << "m2: " << m2 << "ref: " << ref
            << "\niter: " << *iter << '\n';
}

TEST(HashMapTest, try_emplace) {
  HashMap<const char *, std::string> m;

  m.try_emplace("a", "a");
  m.try_emplace("b", "abcd");
  m.try_emplace("c", 10, 'c');
  m.try_emplace("c", "Won't be inserted");

  for (const auto &p : m) {
    std::cout << p.first << " => " << p.second << '\n';
  }
}

TEST(HashMapTest, contains) {
  HashMap<int, std::string> m{{1, "a"}};
  EXPECT_TRUE(m.contains(1));
}

TEST(HashMapTest, count) {
  HashMap<int, std::string> m{{1, "a"}, {1, "b"}};
  for (const auto &p : m) {
    std::cout << p.first << " => " << p.second << '\n';
  }
  EXPECT_EQ(m.count(1), 1);
}

TEST(HashMapTest, equal_range) {
  const HashMap<int, const char *> m{
      {0, "zero"},
      {1, "one"},
      {3, "three"},
  };

  {
    auto p = m.equal_range(1);

    EXPECT_EQ(p.first, m.find(1));
    EXPECT_EQ(p.second, m.find(3));
  }

  {
    auto pp = m.equal_range(-1);

    EXPECT_EQ(pp.first, m.begin());
    EXPECT_EQ(pp.second, m.begin());
  }

  {
    auto ppp = m.equal_range(2);

    EXPECT_EQ(ppp.first, m.find(3));
    EXPECT_EQ(ppp.second, m.find(3));
  }

  {
    auto ppp = m.equal_range(4);

    EXPECT_EQ(ppp.first, m.end());
    EXPECT_EQ(ppp.second, m.end());
  }
}

TEST(HashMapTest, find) {
  const HashMap<int, const char *> m{
      {0, "zero"},
      {1, "one"},
      {3, "three"},
  };

  EXPECT_EQ(m.find(1), m.equal_range(1).first);
  EXPECT_EQ(m.find(2), m.end());
}

TEST(HashMapTest, keys) {
  const HashMap<int, const char *> m{
      {0, "zero"},
      {1, "one"},
      {3, "three"},
  };

  std::list<int> keys = {0, 1, 3};

  EXPECT_EQ(m.keys(), keys);
}

TEST(HashMapTest, values) {
  const HashMap<int, const char *> m{
      {0, "zero"},
      {1, "one"},
      {3, "three"},
  };

  std::list<const char *> values = {"zero", "one", "three"};

  EXPECT_EQ(m.values(), values);
}

TEST(HashMapTest, haskey) {
  const HashMap<int, const char *> m{
      {0, "zero"},
      {1, "one"},
      {3, "three"},
  };

  EXPECT_TRUE(m.hasKey(1));
  EXPECT_FALSE(m.hasKey(4));
}

TEST(HashMapTest, value) {
  const HashMap<int, const char *> m{
      {0, "zero"},
      {1, "one"},
      {3, "three"},
  };

  EXPECT_STREQ(m.value(1, ""), "one");
  EXPECT_STREQ(m.value(4, ""), "");
}

// interface refer to the qt interface.
TEST(HashMapTest, insert_qt) {
  HashMap<int, const char *> m{
      {0, "zero"},
      {1, "one"},
      {3, "three"},
  };

  m.insert(4, "four");

  EXPECT_STREQ(m.value(4, ""), "four");
}

TEST(HashMapTest, clear) {
  HashMap<int, char> container{{1, 'x'}, {2, 'y'}, {3, 'z'}};

  container.clear();

  EXPECT_EQ(container.size(), 0);
  EXPECT_TRUE(container.empty());
}

TEST(HashMapTest, max_size) {
  HashMap<int, char> container{{1, 'x'}, {2, 'y'}, {3, 'z'}};
  HashMap<int, char>::size_type max_size = container.max_size();
}

TEST(HashMapTest, Iterator) {
  HashMap<int, char> container{{1, 'x'}, {2, 'y'}, {3, 'z'}};
  HashMap<int, char>::Iterator iter(&container);
  while (iter.hasNext()) {
    std::cout << iter.value() << std::endl;
    iter = iter.next();
  }
}

TEST(HashMapTest, ConstIterator) {
  HashMap<int, char> container{{1, 'x'}, {2, 'y'}, {3, 'z'}};
  HashMap<int, char>::ConstIterator iter(&container);
  while (iter.hasNext()) {
    int key;
    char value;

    iter.next(&key, &value);
    std::cout << key << "=>" << value << std::endl;
  }
}

TEST(HashMapTest, NoMemberOperator1) {
  HashMap<int, std::string> container1{{1, "x"}, {2, "y"}, {3, "z"}};
  HashMap<int, std::string> container2{{1, "x"}, {2, "y"}, {3, "z"}};

  EXPECT_TRUE(container1 == container2);
}

TEST(HashMapTest, NoMemberOperator3) {
  HashMap<int, std::string> container1{{1, "x1"}, {2, "y1"}, {3, "z1"}};
  HashMap<int, std::string> container2{{1, "x2"}, {2, "y2"}, {3, "z2"}};

  EXPECT_TRUE(container1 != container2);
}

TEST(HashMultimapTest, initializer_list) {
  HashMultimap<int, const char *> hmap = {{1, "test"}, {1, "test1"}};

  std::list<const char *> values = hmap.values(1);

  for (auto value : values) {
    std::cout << value << std::endl;
  }

  EXPECT_TRUE(std::find(values.begin(), values.end(), "test") != values.end());
  EXPECT_TRUE(std::find(values.begin(), values.end(), "test1") != values.end());
}

TEST(HashMultimapTest, copy_constructor) {
  HashMultimap<int, const char *> hmap = {{1, "test"}, {1, "test1"}};
  HashMultimap<int, const char *> hmap1(hmap);

  std::list<const char *> values = hmap.values(1);
  EXPECT_TRUE(std::find(values.begin(), values.end(), "test") != values.end());
  EXPECT_TRUE(std::find(values.begin(), values.end(), "test1") != values.end());
}

TEST(HashMultimapTest, assignmen_operator) {
  HashMultimap<int, const char *> hmap = {{1, "test"}, {1, "test1"}};
  HashMultimap<int, const char *> hmap1 = hmap;

  std::list<const char *> values = hmap.values(1);
  EXPECT_TRUE(std::find(values.begin(), values.end(), "test") != values.end());
  EXPECT_TRUE(std::find(values.begin(), values.end(), "test1") != values.end());
}

TEST(HashMultimapTest, move_constructor) {
  HashMultimap<int, const char *> hmap = {{1, "test"}, {1, "test1"}};
  HashMultimap<int, const char *> hmap1(std::move(hmap));

  std::list<const char *> values = hmap.values(1);
  EXPECT_TRUE(std::find(values.begin(), values.end(), "test") != values.end());
  EXPECT_TRUE(std::find(values.begin(), values.end(), "test1") != values.end());
}

TEST(HashMultimapTest, move_assignment) {
  HashMultimap<int, const char *> hmap = {{1, "test"}, {1, "test1"}};
  HashMultimap<int, const char *> hmap1;
  hmap1 = std::move(hmap);

  std::list<const char *> values = hmap.values(1);
  EXPECT_TRUE(std::find(values.begin(), values.end(), "test") != values.end());
  EXPECT_TRUE(std::find(values.begin(), values.end(), "test1") != values.end());
}

TEST(HashMultimapTest, range_constructor) {
  std::vector<std::pair<int, const char *>> v = {{1, "a"}, {1, "b"}};
  HashMultimap<int, const char *> hmap1(v.begin(), v.end());

  std::list<const char *> values = hmap1.values(1);
  EXPECT_TRUE(std::find(values.begin(), values.end(), "a") != values.end());
  EXPECT_TRUE(std::find(values.begin(), values.end(), "b") != values.end());
}

TEST(HashMultimapTest, count) {
  HashMultimap<int, const char *> hmap = {{1, "test"}, {1, "test1"}};

  EXPECT_EQ(hmap.count(1), 2);
}

TEST(HashMultimapTest, begin) {
  HashMultimap<int, const char *> hmap = {{1, "test"}, {1, "test1"}};

  for (auto p : hmap) {
    std::cout << p.second << std::endl;
  }
}

TEST(HashMultimapTest, Iterator) {
  HashMultimap<const char *, int> hmap = {{"test", 1}, {"test", 2}};
  HashMultimap<const char *, int>::Iterator p(&hmap);

  while (p.hasNext()) {
    std::cout << p.key() << "=>" << p.value() << std::endl;
    p = p.next();
  }

  p.init(&hmap);
  HashMultimap<const char *, int>::Iterator q = p;
  while (q.hasNext()) {
    const char *key;
    int value;
    q.next(&key, &value);
    std::cout << key << "=>" << value << std::endl;
  }

  HashMultimap<const char *, int>::ConstIterator q1(&hmap);
  while (q1.hasNext()) {
    const char *key;
    int value;
    q1.next(&key, &value);
    std::cout << key << "=>" << value << std::endl;
  }
}

TEST(HashMultimapTest, NoMemberOperator1) {
  HashMap<int, std::string> container1{{1, "x"}, {1, "y"}, {3, "z"}};
  HashMap<int, std::string> container2{{1, "x"}, {1, "y"}, {3, "z"}};

  EXPECT_TRUE(container1 == container2);
}

TEST(HashMultimapTest, NoMemberOperator3) {
  HashMap<int, std::string> container1{{1, "x1"}, {1, "y1"}, {3, "z1"}};
  HashMap<int, std::string> container2{{1, "x2"}, {1, "y2"}, {3, "z2"}};

  EXPECT_TRUE(container1 != container2);
}

TEST(HashMultimapTest, swap) {
  HashMap<int, std::string> container1{{1, "x1"}, {1, "y1"}, {3, "z1"}};
  HashMap<int, std::string> container2{{1, "x1"}, {1, "y1"}, {3, "z1"}};

  swap(container1, container2);
}

class Dew {
 public:
  int _a;
  int _b;
  int _c;

  Dew(int a, int b, int c) : _a(a), _b(b), _c(c) {}

  Dew() = default;
  Dew(Dew &&other) = default;
  Dew(const Dew &other) = default;

  Dew &operator=(const Dew &other) = default;
  Dew &operator=(Dew &&other) = default;

  bool operator<(const Dew &other) const {
    if (_a < other._a) return true;
    if (_a == other._a && _b < other._b) return true;
    return (_a == other._a && _b == other._b && _c < other._c);
  }
};

struct DewHash {
  size_t operator()(const Dew &rhs) const {
    return std::hash<int>()(rhs._a) ^ std::hash<int>()(rhs._b) ^
           std::hash<int>()(rhs._c);
  }
};

struct DewCmp {
  bool operator()(const Dew &lhs, const Dew &rhs) const {
    return lhs._a == rhs._a && lhs._b == rhs._b && lhs._b == rhs._b;
  }
};

struct DewGHash {
  size_t operator()(const Dew &rhs) const {
    return HashMap<int, int>::hash()(rhs._a) ^
           HashMap<int, int>::hash()(rhs._b) ^
           HashMap<int, int>::hash()(rhs._c);
  }
};

struct DewGCmp {
  bool operator()(const Dew &lhs, const Dew &rhs) const {
    return lhs._a == rhs._a && lhs._b == rhs._b && lhs._b == rhs._b;
  }
};

auto timeit = [](std::function<int(void)> set_test, std::string what = "") {
  auto start = std::chrono::system_clock::now();
  int setsize = set_test();
  auto stop = std::chrono::system_clock::now();
  std::chrono::duration<double, std::milli> time = stop - start;
  if (what.size() > 0 && setsize > 0) {
    std::cout << std::fixed << std::setprecision(2) << time.count()
              << "  ms for " << what << '\n';
  }
};

TEST(HashMapTest, perf1) {
  constexpr int nof_operations = 20;

  auto map_emplace = [=]() -> int {
    HashMap<Dew, Dew, DewGHash, DewGCmp> hmap;
    for (int i = 0; i < nof_operations; ++i)
      for (int j = 0; j < nof_operations; ++j)
        for (int k = 0; k < nof_operations; ++k)
          hmap.emplace(std::piecewise_construct, std::forward_as_tuple(i, j, k),
                       std::forward_as_tuple(i, j, k));

    return hmap.size();
  };

  auto stl_map_emplace = [=]() -> int {
    std::unordered_map<Dew, Dew, DewHash, DewCmp> hmap;
    for (int i = 0; i < nof_operations; ++i)
      for (int j = 0; j < nof_operations; ++j)
        for (int k = 0; k < nof_operations; ++k)
          hmap.emplace(std::piecewise_construct, std::forward_as_tuple(i, j, k),
                       std::forward_as_tuple(i, j, k));

    return hmap.size();
  };

  // timeit(stl_map_emplace, "stl emplace");
  // timeit(map_emplace, "emplace");
  // timeit(stl_map_emplace, "stl emplace");
  // timeit(map_emplace, "emplace");
}

TEST(HashMapTest, perf2) {
  const int nof_operations = 20;

  auto map_insert = [=]() -> int {
    HashMap<Dew, Dew, DewGHash, DewGCmp> hmap;
    for (int i = 0; i < nof_operations; ++i)
      for (int j = 0; j < nof_operations; ++j)
        for (int k = 0; k < nof_operations; ++k)
          hmap.insert(Dew(i, j, k), Dew(i, j, k));

    return hmap.size();
  };

  auto stl_map_insert = [=]() -> int {
    std::unordered_map<Dew, Dew, DewHash, DewCmp> hmap;
    for (int i = 0; i < nof_operations; ++i)
      for (int j = 0; j < nof_operations; ++j)
        for (int k = 0; k < nof_operations; ++k)
          hmap[Dew(i, j, k)] = Dew(i, j, k);

    return hmap.size();
  };

  timeit(stl_map_insert, "stl insert");
  timeit(map_insert, "insert");
  timeit(stl_map_insert, "stl insert");
  timeit(map_insert, "insert");
}

TEST(HashMapTest, perf3) {
  const int nof_operations = 20;

  HashMap<Dew, Dew, DewGHash, DewGCmp> hmap;
  for (int i = 0; i < nof_operations; ++i)
    for (int j = 0; j < nof_operations; ++j)
      for (int k = 0; k < nof_operations; ++k)
        hmap.insert(Dew(i, j, k), Dew(i, j, k));

  std::unordered_map<Dew, Dew, DewHash, DewCmp> stl_hmap;
  for (int i = 0; i < nof_operations; ++i)
    for (int j = 0; j < nof_operations; ++j)
      for (int k = 0; k < nof_operations; ++k)
        stl_hmap[Dew(i, j, k)] = Dew(i, j, k);

  auto map_find = [=, &hmap]() -> int {
    for (int i = 0; i < nof_operations; ++i)
      for (int j = 0; j < nof_operations; ++j)
        for (int k = 0; k < nof_operations; ++k) hmap.find(Dew(i, j, k));

    return 1;
  };

  auto stl_map_find = [=, &stl_hmap]() -> int {
    for (int i = 0; i < nof_operations; ++i)
      for (int j = 0; j < nof_operations; ++j)
        for (int k = 0; k < nof_operations; ++k) stl_hmap.find(Dew(i, j, k));
    return 1;
  };

  timeit(stl_map_find, "stl find");
  timeit(map_find, "find");
  timeit(stl_map_find, "stl find");
  timeit(map_find, "find");
}

TEST(HashMapTest, perf4) {
  const int nof_operations = 20;

  HashMap<Dew, Dew, DewGHash, DewGCmp> hmap;
  for (int i = 0; i < nof_operations; ++i)
    for (int j = 0; j < nof_operations; ++j)
      for (int k = 0; k < nof_operations; ++k)
        hmap.insert(Dew(i, j, k), Dew(i, j, k));

  std::unordered_map<Dew, Dew, DewHash, DewCmp> stl_hmap;
  for (int i = 0; i < nof_operations; ++i)
    for (int j = 0; j < nof_operations; ++j)
      for (int k = 0; k < nof_operations; ++k)
        stl_hmap[Dew(i, j, k)] = Dew(i, j, k);

  auto map_erase = [=]() mutable -> int {
    for (int i = 0; i < nof_operations; ++i)
      for (int j = 0; j < nof_operations; ++j)
        for (int k = 0; k < nof_operations; ++k) hmap.erase(Dew(i, j, k));

    return 1;
  };

  auto stl_map_erase = [=]() mutable -> int {
    for (int i = 0; i < nof_operations; ++i)
      for (int j = 0; j < nof_operations; ++j)
        for (int k = 0; k < nof_operations; ++k) stl_hmap.erase(Dew(i, j, k));
    return 1;
  };

  timeit(stl_map_erase, "stl erase");
  timeit(map_erase, "erase");
  timeit(stl_map_erase, "stl erase");
  timeit(map_erase, "erase");
}

}  // namespace
