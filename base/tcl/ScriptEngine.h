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

class ScriptEngine {
 public:
  static ScriptEngine* GetOrCreateInstance();
  static void DestroyInstance();

 private:
  ScriptEngine();
  virtual ~ScriptEngine();

  ScriptEngine(const ScriptEngine&) = delete;
  ScriptEngine& operator=(const ScriptEngine&) = delete;

 private:
  static ScriptEngine* _instance;
  Tcl_Interp* _interp;
};
