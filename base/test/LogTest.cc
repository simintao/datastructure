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

TEST_F(LogTest, glogprint) {
  // You can specify one of the following severity levels (in increasing order
  // of severity)
  LOG(INFO) << "info";
  LOG(WARNING) << "warning";
  LOG(ERROR) << "error";
  LOG(FATAL) << "fatal";  // Logging a FATAL message terminates the program
                          // (after the message is logged)!
}
