add_executable(parser_test
  parser_test.cpp
)

target_link_libraries(parser_test
  PRIVATE
    StochasticPARP
    GTest::gtest_main
)

target_include_directories(parser_test
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

set(TEST_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/data)
target_compile_definitions(parser_test
  PRIVATE
    TEST_DATA_DIR="${TEST_DATA_DIR}"
)

include(GoogleTest)
gtest_discover_tests(parser_test)
