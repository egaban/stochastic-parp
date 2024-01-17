#include "parser.cpp"

#include <gtest/gtest.h>
#include <stochastic_parp/parser.h>

const char* const test_file = TEST_DATA_DIR "/instance.txt";

// TEST(ParserTest, ParseFile) {
//   auto graph = read_file(test_file);
//   EXPECT_EQ(graph.vertices().size(), 179);
// }

TEST(ParserTest, SplitWhitespace) {
  auto line = std::string{"1  -2\t\tabc         def 1.0"};
  auto result = split_whitespace(line);

  EXPECT_EQ(result.size(), 5);
  EXPECT_EQ(result[0], "1");
  EXPECT_EQ(result[1], "-2");
  EXPECT_EQ(result[2], "abc");
  EXPECT_EQ(result[3], "def");
  EXPECT_EQ(result[4], "1.0");
}
