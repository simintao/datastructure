
#include <iostream>

#include "Array.h"
#include "ArrayList.h"
#include "gtest/gtest.h"

using namespace std;
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

TEST(ArrayListTest, init) {
  ArrayList<int> a1;
  for (int i = 0; i < 5; i++) {
    int* v = new int(i);
    a1.add(v);
  }
  cout << a1.size() << endl;
  cout << a1.capacity() << endl;
  std::cout << "Hello World!\n";
  // test();
  // ArrayList<Array<Person>>a2;
  // a2.add(arr1);
  // a2.add(arr2);
  // a2.add(arr3);
  // a2.add(arr3);
  // a2.add(arr4);
  /* pcl::Array<Person> arr1(2);
  pcl::Array<Person> arr2(2);
  pcl::Array<Person> arr3(2);
  pcl::Array<Person> arr4(2);
  pcl::Array<Person> arr5(2);
  Person p1("ab", 100);
  Person p2("cd", 30);
  Person p3("dg", 20);
  Person p4("dd", 10);
  Person p5("ghh", 105);
  arr1.pushBack(p1);
  arr2.pushBack(p2);
  arr3.pushBack(p3);
  arr4.pushBack(p4);
  arr5.pushBack(p5);
  ArrayList<pcl::Array<Person>> a2;
  a2.add(&arr1);
  a2.add(&arr2);
  a2.add(&arr3);
  a2.add(&arr4);
  a2.add(&arr5);
  a2.add(&arr3);
  a2.add(&arr3);
  a2.add(&arr3);
  a2.add(&arr3);
  a2.add(&arr3);
  a2.add(&arr3);
  cout << a2.size() << endl;
  cout << a2.capacity() << endl;
  std::cout << "Hello World!\n"; */
  // Iterator<ArrayList<Person>>(a2);
}