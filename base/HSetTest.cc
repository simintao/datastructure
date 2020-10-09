#include "HSet.hh"
#include "gtest/gtest.h"

using pcl::HSet;

namespace {

TEST(SetTest, Ctor) {
  HSet<int> hset = {1, 2, 3};

  EXPECT_TRUE(hset.hasKey(1));
}

} // namespace