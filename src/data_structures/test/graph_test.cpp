#include <data_structures/graph.h>
#include <gtest/gtest.h>

TEST(GraphTest, NumVertices) {
  const auto graph = Graph(123);

  EXPECT_EQ(graph.num_vertices(), 123);
  EXPECT_EQ(graph.vertices().size(), 123);
}
