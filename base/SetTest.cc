#include "Set.h"
#include "gtest/gtest.h"

using pcl::Set;

namespace {

TEST(SetTest, Ctor) {
  Set<int> bset = {1, 2, 3};

  EXPECT_TRUE(bset.hasKey(1));
}

TEST(SetTest, Subtract) {
  Set<int> bset1 = {1, 2, 3};
  Set<int> bset2 = {2, 3, 4};

  bset1.subtract(bset2);

  Set<int> bset3 = {1};

  EXPECT_TRUE(Set<int>::equal(&bset1, &bset3));
}

}  // namespace