/**
 * @file Log.h
 * @author simin tao (taosm@pcl.ac.cn)
 * @brief The file is designed for log utility tool.
 * @version 0.1
 * @date 2020-11-12
 *
 * @copyright Copyright (c) 2020 PCL EDA
 *
 */

#pragma once

#include <iostream>

#include "absl/base/internal/raw_logging.h"
#include "absl/base/log_severity.h"

using absl::LogSeverity;

namespace pcl {

class Log {
 public:
  template <typename... Args>
  static void print(LogSeverity s, Args... args) {
    ABSL_RAW_LOG(INFO, args...);
  }
};

}  // namespace pcl
