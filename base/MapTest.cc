#include "Map.h"
#include "gtest/gtest.h"

using pcl::Map;

namespace {

TEST(MapTest, Ctor) {
  Map<int, const char *> bmap = {{1, "test"}};

  EXPECT_STREQ(bmap.findKey(1), "test");
}

}  // namespace
