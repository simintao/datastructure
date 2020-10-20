#include <iostream>

#include "Array.h"
#include "gtest/gtest.h"

using namespace std;
using namespace pcl;
void printIntArray(Array<int>& arr) {
  for (int i = 0; i < arr.getSize(); i++) {
    std::cout << arr[i] << std::endl;
  }
}
void test01() {
  Array<int> arr1(5);
  for (int i = 0; i < 5; i++) {
    arr1.pushBack(i);
  }

  printIntArray(arr1);

  // Array <int>arr2(arr1);
  // Array<int>arr3(100);
  // arr3 = arr1;
}

class Person {
 public:
  Person(){};
  Person(string name, int age) {
    this->m_Name = name;
    this->m_Age = age;
  }
  string m_Name;
  int m_Age;
};
void printPersonArray(Array<Person>& arr) {
  for (int i = 0; i < arr.getSize(); i++) {
    cout << "name: " << arr[i].m_Name << "age: " << arr[i].m_Age << endl;
  }
}
void test02() {
  Array<Person> arr(10);
  Person p1("11", 100);
  Person p2("dd", 30);
  Person p3("ff", 20);
  Person p4("gg", 10);
  Person p5("hh", 105);
  arr.pushBack(p1);
  arr.pushBack(p2);
  arr.pushBack(p3);
  arr.pushBack(p4);
  arr.pushBack(p5);
  printPersonArray(arr);
  cout << "capacity" << arr.getCapacity() << endl;
  cout << "size" << arr.getSize() << endl;
}
TEST(ArrayTest, init) {
  test01();
  test02();
}
