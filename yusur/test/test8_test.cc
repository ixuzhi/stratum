#include <gtest/gtest.h>

#include <iostream>

struct Fixture : public ::testing::Test {
  virtual void SetUp() {
    std::cout << "SetUp" << std::endl;
    fails = 0;
  }

  virtual void TearDown() {
    if (fails > 0) {
      std::cout << "Fixture::TearDown sees failures:----" << fails << std::endl;
    }
  }

  unsigned fails;
};

TEST_F(Fixture, foo) {
  EXPECT_EQ(1, 0);
  fails += ::testing::Test::HasFailure();
}
TEST_F(Fixture, bar) {
  EXPECT_EQ(1, 1);
  fails += ::testing::Test::HasFailure();
}

TEST_F(Fixture, Three) {
  EXPECT_EQ(1, 2);
  fails += ::testing::Test::HasFailure();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}