
#include "ScriptEngine.h"
#include "gmock/gmock.h"
#include "gtest/gtest-death-test.h"
#include "gtest/gtest.h"

TEST(TclTest, ctor) {
  ScriptEngine* my_engine = ScriptEngine::GetOrCreateInstance();
  ASSERT_TRUE(my_engine);
  ScriptEngine::DestroyInstance();
}