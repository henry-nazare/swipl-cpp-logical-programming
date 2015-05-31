#include "gtest/gtest.h"

#include "PropertyMap.h"

static int glob_argc;
static char **glob_argv;

namespace {

class PropertyMapTest : public ::testing::Test {
  virtual void SetUp() {
    PrologLifetime::begin(glob_argc, glob_argv);
  }

  virtual void TearDown() {
    PrologLifetime::end();
  }
};

TEST_F(PropertyMapTest, FromGenerators) {
  PropertyGenerator<int>
    gen13(std::vector<int>({1, 2, 3})),
    gen24(std::vector<int>({2, 3, 4}));

  PropertyMap<int> map = PropertyMap<int>::fromGenerators({gen13, gen24});
  ASSERT_TRUE(map.lookup(1).isPresent());
  ASSERT_TRUE(map.lookup(2).isPresent());
  ASSERT_TRUE(map.lookup(3).isPresent());
  ASSERT_TRUE(map.lookup(4).isPresent());
}

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  glob_argc = argc;
  glob_argv = argv;
  return RUN_ALL_TESTS();
}

