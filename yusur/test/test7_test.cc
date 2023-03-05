#include <gtest/gtest.h>

class Test2 : public testing::Test {
 protected:
  Test2() { std::cout << "Construct" << std::endl; }
  ~Test2() override { std::cout << "UnConstruct" << std::endl; }
  void SetUp() override { std::cout << "SetUp" << std::endl; }
  void TearDown() override { std::cout << "TearDown" << std::endl; }
};

TEST_F(Test2, test0) {
  EXPECT_EQ(1, 1);
  std::cout << "-----------------1---------------" << std::endl
            << std::endl
            << std::endl;
}

TEST_F(Test2, test1) {
  EXPECT_EQ(1, -1);
  std::cout << "-----------------2---------------" << std::endl;
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}