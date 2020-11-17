// #define GOOGLE_STRIP_LOG 1 // for log serverity test

#include "Log.h"
#include "gmock/gmock.h"
#include "gtest/gtest-death-test.h"
#include "gtest/gtest.h"

using pcl::Log;

class LogTest : public testing::Test {
  void SetUp() {
    char config[] = "test";
    char* argv[] = {config};
    Log::init(argv);

    FLAGS_logtostderr = 1;
  }
  void TearDown() { Log::end(); }
};

TEST_F(LogTest, glogprint) {
  // You can specify one of the following severity levels (in increasing order
  // of severity)
  LOG_INFO << "info";
  LOG_WARNING << "warning";
  LOG_ERROR << "error";
  LOG_FATAL << "fatal";  // Logging a FATAL message terminates the program
                         // (after the message is logged)!
}

TEST_F(LogTest, glogflag) {
  LOG_INFO << "file";
  // Most flags work immediately after updating values.
  FLAGS_logtostderr = 1;
  LOG_INFO << "stderr";
  FLAGS_logtostderr = 0;
  // This won't change the log destination. If you want to set this
  // value, you should do this before google::InitGoogleLogging .
  FLAGS_log_dir = "/home/log/directory";
  LOG_INFO << "the same file";
}

TEST_F(LogTest, glogcondition) {
  int num_cookies = 11;
  LOG_INFO_IF(num_cookies > 10) << "Got lots of cookies";

  LOG_ERROR_EVERY_N(10) << "Got the " << google::COUNTER << "th cookie";

  LOG_WARNING_IF_EVERY_N((num_cookies > 10), 10)
      << "Got the " << google::COUNTER << "th big cookie";

  LOG_FATAL_FIRST_N(20) << "Got the " << google::COUNTER << "th cookie";
}

TEST_F(LogTest, glogdlog) {
  int num_cookies = 11;
  DLOG_INFO << "Found cookies";

  DLOG_WARNING_IF(num_cookies > 10) << "Got lots of cookies";

  DLOG_FATAL_EVERY_N(10) << "Got the " << google::COUNTER << "th cookie";
}

TEST_F(LogTest, check) {
  CHECK_NE(1, 2) << ": The world must be ending!";
  CHECK_EQ(std::string("abc")[1], 'b');
  char* some_ptr = nullptr;
  CHECK_NOTNULL(some_ptr);
}

TEST_F(LogTest, vlog) {
  if (VLOG_IS_ON(1)) {
    // do some logging preparation and logging
    // that can't be accomplished with just VLOG(2) << ...;
    VLOG(0) << "I'm printed when you run the program with --v=1 or higher";
    CHECK_NE(1, 2) << ": The world must be ending!";
  }
}

TEST_F(LogTest, plog) {
  PCHECK(1 < 0) << "Write NULL failed";
  PLOG(INFO) << "Write plog";
}

TEST_F(LogTest, assert) { LOG_ASSERT(1 < 0); }
