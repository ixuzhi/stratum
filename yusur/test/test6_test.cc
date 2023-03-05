#include <gtest/gtest.h>

#include <iostream>

using namespace std;
int Abs(int x) { return x > 0 ? x : -x; }
// Demonstrate some basic assertions.

TEST(t1, EXPECT) {
  EXPECT_TRUE(Abs(1) == 1);
  cout << "EXPECT_TRUE(Abs(1) == 1)" << endl;
  EXPECT_FALSE(Abs(-2) == -2);
  cout << "EXPECT_FALSE(Abs(-2) == -2);" << endl;
  EXPECT_EQ(Abs(1), Abs(-1));
  EXPECT_NE(Abs(-1), 0);
  EXPECT_LT(Abs(-1), 2);
  EXPECT_GT(Abs(-1), 0);
  EXPECT_LE(Abs(-1), 2);
  EXPECT_GE(Abs(-1), 0);
}

TEST(t1, ASSERT) {
  ASSERT_TRUE(Abs(-1) == 1) << "Abs(-1)=1";
  ASSERT_FALSE(Abs(-2) == -2);
  ASSERT_EQ(Abs(1), Abs(-1));
  ASSERT_NE(Abs(-1), 0);
  ASSERT_LT(Abs(-1), 2);
  ASSERT_GT(Abs(-1), 0);
  ASSERT_LE(Abs(-1), 2);
  ASSERT_GE(Abs(-1), 0);
}

TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}