#include "HMap.h"
#include "gtest/gtest.h"

using pcl::HMap;

namespace {

TEST(HMapTest, Ctor) {
  HMap<std::string, const char *> hmap = {{"1", "test"}};

  EXPECT_STREQ(hmap.findKey("1"), "test");
}

}  // namespace
