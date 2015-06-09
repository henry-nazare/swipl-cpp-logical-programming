#include "gtest/gtest.h"

#include "PropertyVault.h"

#include <sstream>

static int glob_argc;
static char **glob_argv;

static PropertyFunctor succ_pred(PropertyVector vector) {
  return PropertyFunctor("succ", vector);
}

namespace {

class PropertyVaultTest : public ::testing::Test {
  virtual void SetUp() {
    PrologLifetime::begin(glob_argc, glob_argv);
  }

  virtual void TearDown() {
    PrologLifetime::end();
  }
};

TEST_F(PropertyVaultTest, ExampleSucc) {
  PropertyGenerator<int> nums(std::vector<int>({1, 2, 3}));
  PropertyGenerator<int> succs(
      nums, (std::function<int (int)>) [](int i) { return i + 1; });

  PropertyMap<int> map = PropertyMap<int>::fromGenerators({nums, succs});
  PropertyBag bag(map, nums, succs);

  PropertyVault vault;
  vault.add(succ_pred, bag);

  PropertyVariable num, succ;
  auto solutions = vault.query(succ_pred({num, succ})).solutions();
  ASSERT_EQ(solutions.size(), 3);
  for (auto &solution : solutions) {
    ASSERT_EQ(map.get(solution, num) + 1, map.get(solution, succ));
  }
}

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  glob_argc = argc;
  glob_argv = argv;
  return RUN_ALL_TESTS();
}

