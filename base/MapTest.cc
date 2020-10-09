#include "Map.hh"
#include "gtest/gtest.h"

using pcl::Map;

namespace {

TEST(MapTest, CopyCtor) {
  Map<int, const char *> bmap = {{1, "test"}};

  EXPECT_STREQ(bmap.findKey(1), "test");
}

} // namespace