#include <thread>

#include "Log.h"
#include "gmock/gmock.h"
#include "gtest/gtest-death-test.h"
#include "gtest/gtest.h"

using pcl::Log;

class LogTest : public testing::Test {
  void SetUp() { Log().init(); }
  void TearDown() {}
};

TEST_F(LogTest, print) {
  src::severity_logger<logging::trivial::severity_level> lg;

  BOOST_LOG_SEV(lg, logging::trivial::info)
      << "thread id: " << std::this_thread::get_id()
      << " Initialization succeeded";
}
