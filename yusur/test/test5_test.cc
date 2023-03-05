#include <gtest/gtest.h>

#include <iostream>
#include <vector>

using namespace std;

class MyClass {
 public:
  MyClass(int _id) : baseValue(_id) {}
  int GetValue() { return baseValue; }
  void Increment(int byValue) { baseValue += byValue; }

 private:
  int baseValue;
};

class Stack {
  vector<int> vstack = {};

 public:
  void push(int value) { vstack.push_back(value); }
  int pop() {
    if (vstack.size() > 0) {
      int value = vstack.back();
      vstack.pop_back();
      return value;
    } else {
      return -1;
    }
  }
  int size() { return vstack.size(); }
};

struct stackTest : public ::testing::Test {
  Stack s1;
  void SetUp() {
    int value[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto& val : value) {
      s1.push(val);
    }
  }
  void TearDown() { cout << "TearDown" << endl; }
};

TEST_F(stackTest, popTest) {
  int lastPopedValue = 9;
  while (lastPopedValue != 1) {
    ASSERT_EQ(s1.pop(), lastPopedValue--);
  }
}

int main(int argc, char** argv) {
  cout << "start----" << endl;
  ::testing::InitGoogleTest(&argc, argv);
  cout << "end----" << endl;
  return RUN_ALL_TESTS();
}