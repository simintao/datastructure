#include "HMap.h"
#include "gtest/gtest.h"

using pcl::HMap;

namespace {

TEST(HMapTest, Ctor) {
  HMap<int, const char *> hmap = {{1, "test"}};

  EXPECT_STREQ(hmap.value(1), "test");
}

}  // namespace
