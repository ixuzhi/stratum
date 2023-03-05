#include <gtest/gtest.h>

#include <iostream>

using namespace std;

void Foo() {
  int* pInt = 0;
  *pInt = 1;
}

TEST(FooTest, test1) { EXPECT_DEATH(Foo(), ""); }

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
