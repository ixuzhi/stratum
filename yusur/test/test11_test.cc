#include <gtest/gtest.h>

#include <iostream>

using namespace std;
TEST(MyDeathTest, TestOne) {
  testing::FLAGS_gtest_death_test_style = "threadsafe";
      // This test is run in the "threadsafe" style:  
      ASSERT_DEATH(ThisShouldDie(), "");
}
TEST(MyDeathTest, TestTwo) {
      // This test is run in the "fast" style:  
      ASSERT_DEATH(ThisShouldDie(), "");
}
int main(intargc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  testing::FLAGS_gtest_death_test_style = "fast";
  return RUN_ALL_TESTS();
}