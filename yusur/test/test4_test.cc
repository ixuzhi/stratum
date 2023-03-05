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

struct MyClassTest : public testing::Test {
  MyClass* mc;
  void SetUp() {
    cout << "alive" << endl;
    mc = new MyClass(100);
  }
  void TearDown() {
    cout << "Dead" << endl;
    delete mc;
  }
};

TEST_F(MyClassTest, Incr_5) {
  mc->Increment(5);
  ASSERT_EQ(mc->GetValue(), 105);
}

TEST_F(MyClassTest, Incr_10) {
  mc->Increment(10);
  ASSERT_EQ(mc->GetValue(), 110);
}

int main(int argc, char** argv) {
  cout << "start----" << endl;
  ::testing::InitGoogleTest(&argc, argv);
  cout << "end----" << endl;
  return RUN_ALL_TESTS();
}