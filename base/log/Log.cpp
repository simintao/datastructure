/**
 * @file Log.cpp
 * @author simin tao (taosm@pcl.ac.cn)
 * @brief The implemention of log utility tool.
 * @version 0.1
 * @date 2020-11-12
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "Log.h"

#include <iostream>
#include <string>

using std::string;

namespace pcl {

void Log::init() {
  string home = "./log/";

  const char config[] = {};
  google::InitGoogleLogging(config);

  string info_log = home + "info_";
  google::SetLogDestination(google::INFO, info_log.c_str());

  string warning_log = home + "warning_";
  google::SetLogDestination(google::WARNING, warning_log.c_str());

  string error_log = home + "error_";
  google::SetLogDestination(google::ERROR, error_log.c_str());

  string fatal_log = home + "fatal_";
  google::SetLogDestination(google::FATAL, fatal_log.c_str());
}
}  // namespace pcl
