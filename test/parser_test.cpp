#include <gtest/gtest.h>

// So we don't have to change the original code, or link
// against GTest.
#define private public
#include <stochastic_parp/parser.h>
#undef private

const char* const test_file = TEST_DATA_DIR "/instance.txt";

class ParserTest : public ::testing::Test {
 protected:
  Parser parser{test_file};
};

TEST_F(ParserTest, NumVertices) {
  auto instance = parser.ParseFile();
  EXPECT_EQ(instance.graph().num_vertices(), 179);
}

TEST_F(ParserTest, NumArcs) {
  auto instance = parser.ParseFile();
  EXPECT_EQ(instance.graph().num_arcs(), 499);
}

TEST_F(ParserTest, NumBlocks) {
  auto instance = parser.ParseFile();
  EXPECT_EQ(instance.num_blocks(), 73);
}

TEST_F(ParserTest, SplitWhitespace) {
  auto line = std::string{"1  -2\t\tabc         def 1.0"};
  auto result = parser.SplitWhitespace(line);

  EXPECT_EQ(result.size(), 5);
  EXPECT_EQ(result[0], "1");
  EXPECT_EQ(result[1], "-2");
  EXPECT_EQ(result[2], "abc");
  EXPECT_EQ(result[3], "def");
  EXPECT_EQ(result[4], "1.0");
}
