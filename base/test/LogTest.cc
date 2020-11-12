#include "Log.h"
#include "gmock/gmock.h"
#include "gtest/gtest-death-test.h"
#include "gtest/gtest.h"

using namespace testing;
using pcl::Log;
TEST(LogTest, print) { Log::print(LogSeverity::kInfo, "%s", "test"); }
