#include "Set.hh"
#include "gtest/gtest.h"

using pcl::Set;

namespace {

TEST(SetTest, Ctor) {
  Set<int> bset = {1, 2, 3};

  EXPECT_TRUE(bset.hasKey(1));
}

} // namespace