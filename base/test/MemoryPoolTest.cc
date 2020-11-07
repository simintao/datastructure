#include "MemoryPool.h"
#include "gmock/gmock.h"
#include "gtest/gtest-death-test.h"
#include "gtest/gtest.h"

using namespace testing;

using pcl::ObjectPool;

namespace {

class A {
  std::string _str;

 public:
  explicit A(std::string str) : _str(str) {}
  A(const A& other) : _str(other._str) {
    std::cout << "copy"
              << "\n";
  }

  A(A&& other) : _str(std::move(other._str)) {
    std::cout << "move"
              << "\n";
  }

  ~A() {
    // std::cout << "desctructor"
    //<< "\n";
  }

  A& operator=(const A& other) {
    _str = other._str;
    std::cout << "copy"
              << "\n";
    return *this;
  }

  A& operator=(A&& other) {
    _str = std::move(other._str);
    std::cout << "move"
              << "\n";
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, A const& rhs) {
    os << rhs._str;
    return os;
  }
};

A func(const A& test) {
  A test1 = std::move(test);
  return test1;
}

A func(A&& test) {
  A test1 = test;
  return test1;
}

TEST(MemoryPoolTest, construct) {
  //   A test("test");

  //   // auto test1 = test;
  //   auto& test2 = test;
  //   auto&& test3 = test;

  //   auto test4 = func(test);
  //   auto& test5 = func(std::move(test));
  //   auto&& test6 = func(std::move(test));

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
  constexpr size_t count = 1000;
  ObjectPool<A> p(count);
  auto boost_func = [&p]() -> int {
    for (size_t i = 0; i < count; ++i) {
      A* const t = p.construct("test");
      // std::cout << *t << std::endl;
      // p.destroy(t);
      // Do something with t; don't take the time to free() it
    }
    return 1;
  };  // on function exit, p is destroyed, and all destructors for the X objects
      // are called

  auto stl_func = []() -> int {
    for (size_t i = 0; i < count; ++i) {
      A* const t = new A("test");
      // std::cout << *t << std::endl;
      // delete t;
      // Do something with t; don't take the time to free() it
    }
    return 1;
  };

  timeit(boost_func, "boost");
  timeit(stl_func, "stl");
  timeit(boost_func, "boost");
  timeit(stl_func, "stl");
}
}  // namespace