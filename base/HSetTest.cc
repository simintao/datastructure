#include <chrono>
#include <functional>
#include <memory>
#include <utility>

#include "HSet.h"
#include "gtest/gtest.h"

using pcl::HMultiset;
using pcl::HSet;

namespace {

TEST(HSetTest, Ctor) {
  HSet<int> hset = {1, 2, 3};

  EXPECT_TRUE(hset.hasKey(1));
}

TEST(HSetTest, Subtract) {
  HSet<int> hset1 = {1, 2, 3};
  HSet<int> hset2 = {2, 3, 4};

  hset1.subtract(hset2);

  HSet<int> hset3 = {1};

  EXPECT_TRUE(HSet<int>::equal(&hset1, &hset3));
}

TEST(HSetTest, swap) {
  HSet<int> hset1 = {1, 2, 3};
  HSet<int> hset2 = {2, 3, 4};

  swap(hset1, hset2);

  EXPECT_FALSE(hset1.hasKey(1));
}

TEST(HSetTest, extract) {
  HSet<int> cont = {1, 2, 3};

  auto print = [](int p) { std::cout << " " << p; };

  std::cout << "Start:";
  std::for_each(cont.begin(), cont.end(), print);
  std::cout << '\n';

  // Extract node handle and change key
  auto nh = cont.extract(cont.begin());

  std::cout << "After extract and before insert:";
  std::for_each(cont.begin(), cont.end(), print);
  std::cout << '\n';

  // Insert node handle back
  cont.insert(move(nh));

  std::cout << "End:";
  std::for_each(cont.begin(), cont.end(), print);
  std::cout << '\n';

  EXPECT_TRUE(HSet<int>::equal(&cont, &cont));
}

TEST(HSetTest, equal) {
  HSet<int> cont = {1, 2, 3};
  HSet<int> cont1 = {1, 2, 3};

  EXPECT_TRUE(HSet<int>::equal(&cont, &cont1));
}

TEST(HSetTest, operator1) {
  HSet<int> cont = {1, 2, 3};
  cont << 4;
  for (auto& p : cont) {
    std::cout << p << std::endl;
  }
}

TEST(HSetTest, operator2) {
  HSet<int> cont = {1, 2, 3};
  HSet<int> cont1 = {4, 5, 6};

  cont |= cont1;

  for (auto& p : cont) {
    std::cout << p << std::endl;
  }
}

TEST(HSetTest, operator3) {
  HSet<int> cont = {1, 2, 3};
  HSet<int> cont1 = {4, 5, 6};

  cont |= std::move(cont1);

  for (auto& p : cont) {
    std::cout << p << std::endl;
  }

  HSet<int> result = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(cont, result);
}

TEST(HSetTest, operator4) {
  HSet<int> cont = {1, 2, 3};

  cont |= 4;

  for (auto& p : cont) {
    std::cout << p << std::endl;
  }

  HSet<int> result = {1, 2, 3, 4};
  EXPECT_EQ(cont, result);
}

TEST(HSetTest, operator5) {
  HSet<int> cont = {1, 2, 3};
  HSet<int> cont1 = {2, 3, 4};

  cont &= cont1;

  for (auto& p : cont) {
    std::cout << p << std::endl;
  }

  HSet<int> result = {2, 3};
  EXPECT_EQ(cont, result);
}

TEST(HSetTest, operator6) {
  HSet<int> cont = {1, 2, 3};

  cont &= 3;

  for (auto& p : cont) {
    std::cout << p << std::endl;
  }

  HSet<int> result = {3};
  EXPECT_EQ(cont, result);
}

TEST(HSetTest, operator7) {
  HSet<int> cont = {1, 2, 3};

  cont += 4;

  for (auto& p : cont) {
    std::cout << p << std::endl;
  }

  HSet<int> result = {1, 2, 3, 4};
  EXPECT_EQ(cont, result);
}

TEST(HSetTest, operator8) {
  HSet<int> cont = {1, 2, 3};

  cont += {4};

  for (auto& p : cont) {
    std::cout << p << std::endl;
  }

  HSet<int> result = {1, 2, 3, 4};
  EXPECT_EQ(cont, result);
}

TEST(HSetTest, operator9) {
  HSet<int> cont = {1, 2, 3, 4};

  cont -= {4};

  for (auto& p : cont) {
    std::cout << p << std::endl;
  }

  HSet<int> result = {1, 2, 3};
  EXPECT_EQ(cont, result);
}

TEST(HSetTest, operator10) {
  HSet<int> cont = {1, 2, 3, 4};

  cont -= 4;

  for (auto& p : cont) {
    std::cout << p << std::endl;
  }

  HSet<int> result = {1, 2, 3};
  EXPECT_EQ(cont, result);
}

TEST(HSetTest, operator11) {
  HSet<int> cont = {1, 2, 3, 4};
  HSet<int> cont1 = {5};

  cont = cont | cont1;

  for (auto& p : cont) {
    std::cout << p << std::endl;
  }

  HSet<int> result = {1, 2, 3, 4, 5};
  EXPECT_EQ(cont, result);
}

TEST(HSetTest, operator12) {
  HSet<int> cont = {1, 2, 3, 4};
  HSet<int> cont1 = {4};

  cont = cont & cont1;

  for (auto& p : cont) {
    std::cout << p << std::endl;
  }

  HSet<int> result = {4};
  EXPECT_EQ(cont, result);
}

TEST(HSetTest, operator13) {
  HSet<int> cont = {1, 2, 3, 4};
  HSet<int> cont1 = {5};

  cont = cont + cont1;

  for (auto& p : cont) {
    std::cout << p << std::endl;
  }

  HSet<int> result = {1, 2, 3, 4, 5};
  EXPECT_EQ(cont, result);
  EXPECT_TRUE(cont1.empty());
}

TEST(HSetTest, operator14) {
  HSet<int> cont = {1, 2, 3, 4, 5};
  HSet<int> cont1 = {5};

  cont = cont - cont1;

  for (auto& p : cont) {
    std::cout << p << std::endl;
  }

  HSet<int> result = {1, 2, 3, 4};
  EXPECT_EQ(cont, result);
}

TEST(HSetTest, haskey) {
  HSet<int> cont = {1, 2, 3, 4, 5};
  EXPECT_TRUE(cont.hasKey(4));
}

TEST(HSetTest, issuhset) {
  HSet<int> cont = {1, 2, 3, 4, 5};
  HSet<int> cont1 = {1, 2, 3};
  EXPECT_TRUE(cont.isSubset(&cont1));
}

TEST(HSetTest, insertset) {
  HSet<int> cont = {1, 2, 3, 4, 5};
  HSet<int> cont1 = {1, 2, 3, 6};
  cont.insertSet(&cont1);
  HSet<int> result = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(cont, result);
}

TEST(HSetTest, intersects) {
  HSet<int> cont = {1, 2, 3, 4, 5};
  HSet<int> cont1 = {1, 2, 3, 6};
  EXPECT_TRUE(HSet<int>::intersects(&cont, &cont1));
}

TEST(HSetTest, nonmember1) {
  HSet<int> cont = {1, 2, 3, 4, 5};
  HSet<int> cont1 = {1, 2, 3};

  EXPECT_FALSE(cont == cont1);
}

TEST(HSetTest, nonmember2) {
  HSet<int> cont = {1, 2, 3, 4, 5};
  HSet<int> cont1 = {1, 2, 3, 6};

  EXPECT_TRUE(cont != cont1);
}

TEST(HSetTest, nonmember7) {
  HSet<int> cont = {1, 2, 3, 5, 7};
  HSet<int> cont1 = {1, 2, 3, 5, 6};

  swap(cont, cont1);

  HSet<int> result_cont = {1, 2, 3, 5, 6};

  EXPECT_EQ(cont, result_cont);
}

TEST(HMultisetTest, ctor) {
  HMultiset<int> hmultiset = {1, 2, 2, 3};
  for (auto item : hmultiset) {
    std::cout << item << std::endl;
  }
}

TEST(HMultisetTest, capacity) {
  HMultiset<int> hmultiset;

  EXPECT_TRUE(hmultiset.empty());

  std::cout << "max size : " << hmultiset.max_size() << std::endl;
}

TEST(HMultisetTest, modifier1) {
  HMultiset<std::unique_ptr<int, std::function<void(int*)>>> hmultiset;
  auto deleter = [](int* p) {
    std::cout << "delete " << *p << std::endl;
    delete p;
  };

  hmultiset.emplace(new int(2), deleter);
  hmultiset.emplace_hint(hmultiset.begin(), new int(1), deleter);

  std::cout << "remove one element" << std::endl;
  hmultiset.erase(++hmultiset.begin());
  std::cout << "add one element" << std::endl;
  hmultiset.emplace(new int(3), deleter);
}

TEST(HMultisetTest, swap) {
  HMultiset<int> hmultiset1 = {1, 2, 3};
  HMultiset<int> hmultiset2 = {2, 3, 4};

  hmultiset1.swap(hmultiset2);

  for (auto& p : hmultiset1) {
    std::cout << p << std::endl;
  }

  HMultiset<int> result = {2, 3, 4};
  EXPECT_EQ(hmultiset1, result);
}

TEST(HMultisetTest, lookup) {
  HMultiset<int> hmultiset1 = {1, 1, 3};

  auto range = hmultiset1.equal_range(1);
  for (auto p = range.first; p != range.second; p++) {
    std::cout << *p << std::endl;
  }
}

TEST(HMultisetTest, nonmember1) {
  HMultiset<int> hmultiset1 = {1, 2, 3};
  HMultiset<int> hmultiset2 = {2, 3, 4};

  EXPECT_FALSE(hmultiset1 == hmultiset2);
}

TEST(HMultisetTest, nonmember2) {
  HMultiset<int> hmultiset1 = {1, 2, 3};
  HMultiset<int> hmultiset2 = {2, 3, 4};

  EXPECT_TRUE(hmultiset1 != hmultiset2);
}

TEST(HMultisetTest, nonmember7) {
  HMultiset<int> hmultiset1 = {1, 2, 3};
  HMultiset<int> hmultiset2 = {2, 3, 4};

  swap(hmultiset1, hmultiset2);

  HMultiset<int> result = {2, 3, 4};

  EXPECT_EQ(hmultiset1, result);
}

class Dew {
 public:
  int _a;
  int _b;
  int _c;

  Dew(int a, int b, int c) : _a(a), _b(b), _c(c) {}

  bool operator<(const Dew& other) const {
    if (_a < other._a) return true;
    if (_a == other._a && _b < other._b) return true;
    return (_a == other._a && _b == other._b && _c < other._c);
  }
};

struct DewHash {
  size_t operator()(const Dew& rhs) const {
    return std::hash<int>()(rhs._a) ^ std::hash<int>()(rhs._b) ^
           std::hash<int>()(rhs._c);
  };
};

struct DewCmp {
  bool operator()(const Dew& lhs, const Dew& rhs) const {
    return lhs._a == rhs._a && lhs._b == rhs._b && lhs._b == rhs._b;
  };
};

struct DewGHash {
  size_t operator()(const Dew& rhs) const {
    return HSet<int>::hash()(rhs._a) ^ HSet<int>::hash()(rhs._b) ^
           HSet<int>::hash()(rhs._c);
  };
};

struct DewGCmp {
  bool operator()(const Dew& lhs, const Dew& rhs) const {
    return lhs._a == rhs._a && lhs._b == rhs._b && lhs._b == rhs._b;
  };
};

auto timeit = [](std::function<int()> set_test, std::string what = "") {
  auto start = std::chrono::system_clock::now();
  int setsize = set_test();
  auto stop = std::chrono::system_clock::now();
  std::chrono::duration<double, std::milli> time = stop - start;
  if (what.size() > 0 && setsize > 0) {
    std::cout << std::fixed << std::setprecision(2) << time.count()
              << "  ms for " << what << '\n';
  }
};

TEST(HSetTest, perf1) {
  const int nof_operations = 10;

  auto set_insert = []() -> int {
    HSet<Dew, DewGHash, DewGCmp> set;
    for (int i = 0; i < nof_operations; ++i)
      for (int j = 0; j < nof_operations; ++j)
        for (int k = 0; k < nof_operations; ++k) set.insert(Dew(i, j, k));

    return set.size();
  };

  auto stl_set_insert = []() -> int {
    std::unordered_set<Dew, DewHash, DewCmp> set;
    for (int i = 0; i < nof_operations; ++i)
      for (int j = 0; j < nof_operations; ++j)
        for (int k = 0; k < nof_operations; ++k) set.insert(Dew(i, j, k));

    return set.size();
  };

  timeit(stl_set_insert, "stl insert");
  timeit(set_insert, "insert");
  timeit(stl_set_insert, "stl insert");
  timeit(set_insert, "insert");
}

TEST(HSetTest, perf2) {
  const int nof_operations = 10;

  HSet<Dew, DewGHash, DewGCmp> set;
  for (int i = 0; i < nof_operations; ++i)
    for (int j = 0; j < nof_operations; ++j)
      for (int k = 0; k < nof_operations; ++k) set.insert(Dew(i, j, k));

  std::unordered_set<Dew, DewHash, DewCmp> stl_set;
  for (int i = 0; i < nof_operations; ++i)
    for (int j = 0; j < nof_operations; ++j)
      for (int k = 0; k < nof_operations; ++k) stl_set.insert(Dew(i, j, k));

  auto set_find = [&]() -> int {
    for (int i = 0; i < nof_operations; ++i)
      for (int j = 0; j < nof_operations; ++j)
        for (int k = 0; k < nof_operations; ++k) set.find(Dew(i, j, k));

    return 1;
  };

  auto stl_set_find = [&]() -> int {
    for (int i = 0; i < nof_operations; ++i)
      for (int j = 0; j < nof_operations; ++j)
        for (int k = 0; k < nof_operations; ++k) stl_set.find(Dew(i, j, k));
    return 1;
  };

  timeit(stl_set_find, "stl find");
  timeit(set_find, "find");
  timeit(stl_set_find, "stl find");
  timeit(set_find, "find");
}

TEST(HSetTest, perf3) {
  const int nof_operations = 10;

  HSet<Dew, DewGHash, DewGCmp> set;
  for (int i = 0; i < nof_operations; ++i)
    for (int j = 0; j < nof_operations; ++j)
      for (int k = 0; k < nof_operations; ++k) set.insert(Dew(i, j, k));

  std::unordered_set<Dew, DewHash, DewCmp> stl_set;
  for (int i = 0; i < nof_operations; ++i)
    for (int j = 0; j < nof_operations; ++j)
      for (int k = 0; k < nof_operations; ++k) stl_set.insert(Dew(i, j, k));

  auto set_erase = [=]() mutable -> int {
    for (int i = 0; i < nof_operations; ++i)
      for (int j = 0; j < nof_operations; ++j)
        for (int k = 0; k < nof_operations; ++k) set.erase(Dew(i, j, k));

    return 1;
  };

  auto stl_set_erase = [=]() mutable -> int {
    for (int i = 0; i < nof_operations; ++i)
      for (int j = 0; j < nof_operations; ++j)
        for (int k = 0; k < nof_operations; ++k) stl_set.erase(Dew(i, j, k));
    return 1;
  };

  timeit(stl_set_erase, "stl erase");
  timeit(set_erase, "erase");
  timeit(stl_set_erase, "stl erase");
  timeit(set_erase, "erase");
}

}  // namespace