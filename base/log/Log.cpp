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

namespace pcl {

void Log::init() {
  boost::log::register_simple_formatter_factory<
      boost::log::trivial::severity_level, char>("Severity");
  logging::add_file_log(
      keywords::file_name = "./sign_%Y-%m-%d_%H-%M-%S.%N.log",
      keywords::rotation_size = 10 * 1024 * 1024,
      keywords::time_based_rotation =
          sinks::file::rotation_at_time_point(0, 0, 0),
      keywords::format = "[%TimeStamp%] (%Severity%) : %Message%",
      keywords::min_free_space = 3 * 1024 * 1024);
  logging::core::get()->set_filter(logging::trivial::severity >=
                                   logging::trivial::debug);

  logging::add_common_attributes();
}

}  // namespace pcl
