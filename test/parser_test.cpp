#include <gtest/gtest.h>

#include <algorithm>

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
  EXPECT_EQ(instance->graph().num_vertices(), 179);
}

TEST_F(ParserTest, Blocks) {
  auto instance = parser.ParseFile();

  EXPECT_EQ(instance->blocks_.size(), 73);

  EXPECT_EQ(instance->graph().vertices_[7]->blocks_.size(), 4);
}

TEST_F(ParserTest, NumArcs) {
  auto instance = parser.ParseFile();
  EXPECT_EQ(instance->graph().num_arcs(), 499);
}

TEST_F(ParserTest, ArcsExist) {
  auto instance = parser.ParseFile();

  auto vertex = instance->graph().vertices_[2];
  EXPECT_EQ(vertex->outgoing_arcs_.size(), 4);
  EXPECT_NE(std::ranges::find(instance->graph_.vertices_, vertex),
            instance->graph_.vertices_.end());

  auto arc = vertex->outgoing_arcs_[0].lock();
  EXPECT_EQ(arc->from_.lock(), vertex);
  EXPECT_EQ(arc->to_.lock(), instance->graph().vertices_[66]);
  EXPECT_EQ(arc->profit_, 2);
  EXPECT_EQ(arc->size_, 27.1);

  EXPECT_NE(std::ranges::find(instance->graph_.arcs_, arc),
            instance->graph_.arcs_.end());

  EXPECT_EQ(arc->block_.has_value(), true);
  EXPECT_EQ(arc->block_.value().lock()->id_, 58);
}

TEST_F(ParserTest, NumBlocks) {
  auto instance = parser.ParseFile();
  EXPECT_EQ(instance->blocks().size(), 73);
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

TEST_F(ParserTest, ParseBlocks) {
  auto line = std::string{"-1,2,3,4,5"};
  auto result = parser.ParseBlocks(line);

  EXPECT_EQ(result.size(), 5);
  EXPECT_EQ(result[0], -1);
  EXPECT_EQ(result[1], 2);
  EXPECT_EQ(result[2], 3);
  EXPECT_EQ(result[3], 4);
  EXPECT_EQ(result[4], 5);
}
