add_executable(data_structures_test
  graph_test.cpp
)

target_link_libraries(data_structures_test
  data_structures
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(data_structures_test)
