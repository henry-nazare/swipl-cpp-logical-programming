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
  PropertyGenerator<int> nums(
      std::vector<int>({1, 2, 3}),
      (std::function<int (int)>) [](int i) { return i; });
  PropertyGenerator<int> succs(
      nums, (std::function<int (int)>) [](int i) { return i + 1; });

  PropertyMap<int> map;
  map.put(PropertyValue(), 1);
  map.put(PropertyValue(), 2);
  map.put(PropertyValue(), 3);
  map.put(PropertyValue(), 4);

  PropertyBag bag(map, nums, succs);

  PropertyVault vault;
  vault.add(succ_pred, bag);

  PropertyVariable num, succ;
  int solutions = 0;
  vault.query(succ_pred({num, succ}), [&]() {
    ASSERT_EQ(map.get(num.get()) + 1, map.get(succ.get()));
    solutions = solutions + 1;
  });
  ASSERT_EQ(solutions, 3);
}

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  glob_argc = argc;
  glob_argv = argv;
  return RUN_ALL_TESTS();
}

