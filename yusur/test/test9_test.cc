#include <gtest/gtest.h>

#include <iostream>

using namespace std;
class FooEnv : public testing::Environment {
 public:
  void SetUp() { std::cout << "Environment SetUp" << endl; }
  virtual void TearDown() { cout << "Environment TearDown" << endl; }
};

TEST(FooEnv, test9) { EXPECT_EQ(7 * 6, 42); }

int main(int argc, char** argv) {
  testing::AddGlobalTestEnvironment(new FooEnv);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}