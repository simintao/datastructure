#include "HSet.h"
#include "gtest/gtest.h"

using pcl::HSet;

namespace {

TEST(HSetTest, Ctor) {
  HSet<int> hset = {1, 2, 3};

  EXPECT_TRUE(hset.hasKey(1));
}

} // namespace