cmake_minimum_required(VERSION 2.6)

enable_testing()

link_directories(${GTEST_LIBS_DIR})
include_directories("${GTEST_INCLUDE_DIRS}")

function(add_gtest_all_tests SRC_FILE EXE)
  file(READ "${SRC_FILE}" CONTENTS)

  set(ALPHA "a-zA-Z_")
  set(ALPHANUM "${ALPHA}0-9")
  set(SPACES "[ ]*")

  set(IDENT_REGEX "([${ALPHA}][${ALPHANUM}]*)")
  set(TEST_REGEX "TEST_F\\([ ]*${IDENT_REGEX}[ ]*,[ ]*${IDENT_REGEX}[ ]*\\)")

  string(REGEX MATCHALL "${TEST_REGEX}" TESTS ${CONTENTS})
  foreach(TEST ${TESTS})
    string(REGEX MATCHALL "${TEST_REGEX}" _ ${TEST})
    set(TEST_NAME "${CMAKE_MATCH_1}.${CMAKE_MATCH_2}")
    add_test(${TEST_NAME} ${EXE} --gtest_filter=${TEST_NAME} "")
  endforeach()
endfunction()

function(add_gtest_test PREFIX)
  add_executable(${PREFIX} ${PREFIX}.cpp)
  target_link_libraries(${PREFIX} ${GTEST_BOTH_LIBS} swipl swiplcpplp)
  add_gtest_all_tests(${PREFIX}.cpp ${PREFIX})
endfunction()

add_gtest_test(PropertyMapTest)
add_gtest_test(PropertyVaultTest)

