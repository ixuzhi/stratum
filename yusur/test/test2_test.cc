#include <gtest/gtest.h>

#include <iostream>

using namespace std;

class MyClass {
 public:
  MyClass(string _id) : id(_id) {}
  string GetId() { return id; }

 private:
  string id;
};

TEST(TestName, MyClass) {
  MyClass mc("root");
  string value = mc.GetId();
  ASSERT_STREQ(value.c_str(), "root");
  ASSERT_EQ(value, "root");
  ASSERT_NE(value, "root");
}

int main(int argc, char** argv) {
  cout << "start----" << endl;
  ::testing::InitGoogleTest(&argc, argv);
  cout << "end----" << endl;
  return RUN_ALL_TESTS();
}