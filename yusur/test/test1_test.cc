#include <gtest/gtest.h>

#include <iostream>

using namespace std;
TEST(TestName, Subtest1) {
  cout << "start" << endl;
  ASSERT_TRUE(1 == 1);
  ASSERT_FALSE(1 == 2);
  cout << "end" << endl;
}

int main(int argc, char** argv) {
  cout << "start----" << endl;
  ::testing::InitGoogleTest(&argc, argv);
  cout << "end----" << endl;
  return RUN_ALL_TESTS();
}