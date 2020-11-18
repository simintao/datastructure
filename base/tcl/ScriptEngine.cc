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

/**
 * @brief Get the script engine or create one.
 *
 * @return ScriptEngine* The script engine.
 */
ScriptEngine* ScriptEngine::getOrCreateInstance() {
  static std::mutex mt;
  if (_instance == nullptr) {
    std::lock_guard<std::mutex> lock(mt);
    if (_instance == nullptr) {
      _instance = new ScriptEngine();
    }
  }
  return _instance;
}

/**
 * @brief Close the script engine.
 *
 */
void ScriptEngine::destroyInstance() {
  delete _instance;
  _instance = nullptr;
}

/**
 * @brief Call the tcl interpreter to execuate the tcl file.
 *
 * @param file_name The script file.
 * @return int
 */
int ScriptEngine::evalScriptFile(const char* file_name) {
  return Tcl_Eval(_interp, file_name);
}

/**
 * @brief Append the cmd execuate result to tcl interpretr.
 *
 * @param result The cmd execuate result.
 */
void ScriptEngine::appendResult(char* result) {
  Tcl_AppendResult(_interp, result, nullptr);
}

/**
 * @brief Get the result from interpreter.
 *
 * @return const char*
 */
const char* ScriptEngine::getResult() { return Tcl_GetStringResult(_interp); }
