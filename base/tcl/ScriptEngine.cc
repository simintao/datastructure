/**
 * @file ScriptEngine.cpp
 * @author simin tao (taosm@pcl.ac.cn)
 * @brief The file is the implementation of the script engine based on tcl.
 * @version 0.1
 * @date 2020-11-18
 *
 * @copyright Copyright (c) 2020 pcl EDA.
 *
 */

#include "ScriptEngine.h"

ScriptEngine* ScriptEngine::_instance = nullptr;

ScriptEngine::ScriptEngine() { _interp = Tcl_CreateInterp(); }
ScriptEngine::~ScriptEngine() { Tcl_DeleteInterp(_interp); }

ScriptEngine* ScriptEngine::GetOrCreateInstance() {
  static std::mutex mt;
  if (_instance == nullptr) {
    std::lock_guard<std::mutex> lock(mt);
    if (_instance == nullptr) {
      _instance = new ScriptEngine();
    }
  }
  return _instance;
}

void ScriptEngine::DestroyInstance() {
  delete _instance;
  _instance = nullptr;
}