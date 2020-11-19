/**
 * @file ScriptEnginer.h
 * @author simin tao (taosm@pcl.ac.cn)
 * @brief The file is the class of the script engine based on tcl.
 * @version 0.1
 * @date 2020-11-18
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include <mutex>

#include "tcl.h"

/**
 * @brief The ScriptEngine is used for tcl file process such as sdc file.
 *
 */
class ScriptEngine {
 public:
  static ScriptEngine* getOrCreateInstance();
  static void destroyInstance();

 private:
  ScriptEngine();
  virtual ~ScriptEngine();

  ScriptEngine(const ScriptEngine&) = delete;
  ScriptEngine& operator=(const ScriptEngine&) = delete;

  int evalScriptFile(const char* file_name);

  void appendResult(char* result);
  const char* getResult();

 private:
  static ScriptEngine* _instance;  //!< The singleton instance.
  Tcl_Interp* _interp;             //!< The tcl interpreter.
};
