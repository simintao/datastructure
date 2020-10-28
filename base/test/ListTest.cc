#include <iostream>

#include "List.h"
#include "gtest/gtest.h"
TEST(ListTest, base) {
  pcl::List<int> el;
  el.push_back(1);
  el.push_back(2);
  el.push_back(3);
  el.push_back(4);
  el.push_back(5);
  el.push_back(6);
  int size = el.size();
  int mSize = el.max_size();
  std::cout << size << std::endl;
  std::cout << mSize << std::endl;
  el.resize(0);
  std::cout << el.size() << std::endl;
  if (el.empty()) {
    std::cout << "元素为空" << std::endl;
  }
  el.push_front(7);
}
TEST(ListTest, addElements) {
  pcl::List<int> el;
  el.push_back(1);
  el.push_back(2);
  el.push_back(3);
  el.push_back(4);
  el.push_back(5);
  el.push_back(6);
  el.push_front(7);
  pcl::List<int>::iterator it = el.begin();
  el.insert(it, 8);
  el.insert(el.begin(), 3, 9);
  pcl::List<int> el2(5, 10);
  el.insert(el.begin(), el2.begin(), ++el2.begin());
  for (it = el.begin(); it != el.end(); it++) {
    std::cout << *it << std::endl;
  }
}
TEST(ListTest, deleteElements) {
  pcl::List<int> el;
  el.push_back(1);
  el.push_back(2);
  el.push_back(3);
  el.push_back(4);
  el.push_back(5);
  el.push_back(6);
  el.pop_front();
  el.pop_back();
  pcl::List<int>::iterator it = el.begin();
  el.erase(it);
  el.erase(el.begin(), ++el.begin());

  for (it = el.begin(); it != el.end(); it++) {
    std::cout << *it << std::endl;
  }
}
TEST(ListTest, getElements) {
  pcl::List<int> el;
  el.push_back(1);
  el.push_back(2);
  el.push_back(3);
  el.push_back(4);
  el.push_back(5);
  el.push_back(6);

  std::cout << el.front() << std::endl;
  std::cout << el.back() << std::endl;
}
TEST(ListTest, others) {
  pcl::List<int> el;
  pcl::List<int> el2;
  el.push_back(1);
  el.push_back(2);
  el.push_back(3);
  el.push_back(4);
  el.push_back(5);
  el.push_back(6);
  el2.assign(6, 7);

  std::cout << el.front() << std::endl;
  std::cout << el.back() << std::endl;
  swap(el, el2);

  for (pcl::List<int>::iterator it = el.begin(); it != el.end();
       it++) {
    std::cout << *it << " ";
  }
  std::cout << std ::endl;
  el.splice(el.end(), el2);

  for (pcl::List<int>::iterator it1 = el.begin(); it1 != el.end();
       it1++) {
    std::cout << *it1 << " ";
  }
  std::cout << std ::endl;
  pcl::List<int> el3(3, 5);
  pcl::List<int> el4(3, 7);
  pcl::List<int> el5 = el3 + el4;
  el5 += 8;
  // el3.unique();
  for (pcl::List<int>::iterator it2 = el5.begin(); it2 != el5.end();
       it2++) {
    std::cout << *it2 << " ";
  }
}
TEST(ListTest, iterator) {
  pcl::List<int> el;
  el.push_back(1);
  el.push_back(2);
  el.push_back(3);
  std::cout << *(el.begin()) << std::endl;
  std::cout << *(--el.end()) << std::endl;
  std::cout << *(el.cbegin()) << std::endl;
  std::cout << *(--el.cend()) << std::endl;
  std::cout << *(el.rbegin()) << std::endl;
  std::cout << *(--el.rend()) << std::endl;
}
TEST(ListTest, operator) {
  pcl::List<int> el1;
  pcl::List<int> el2;
  el1.push_back(1);
  el1.push_back(2);
  el1.push_back(3);
  el2.push_back(4);
  el2.push_back(5);
  el2.push_back(6);

  bool isEqual = (el1 == el2) ? true : false;
  bool nEqual = (el1 != el2) ? true : false;
  bool compare1 = (el1 < el2) ? true : false;
  bool compare2 = (el1 > el2) ? true : false;
  std::cout << isEqual << std::endl;
  std::cout << nEqual << std::endl;
  std::cout << compare1 << std::endl;
  std::cout << compare2 << std::endl;
}
