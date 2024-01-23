#define private public
#include <data_structures/graph.h>
#undef private

#include <gtest/gtest.h>

TEST(GraphTest, NumVertices) {
  const auto graph = Graph(123);

  EXPECT_EQ(graph.num_vertices(), 123);
  EXPECT_EQ(graph.vertices().size(), 123);
}

TEST(GraphTest, TotalCost) {
  auto graph = Graph(3);
  EXPECT_EQ(graph.total_cost(), 0);

  const auto vertex1 = graph.vertices_[0];
  const auto vertex2 = graph.vertices_[1];
  const auto vertex3 = graph.vertices_[2];

  const auto arc1 = std::make_shared<Arc>(vertex1, vertex2, std::nullopt, 1, 2);
  const auto arc2 = std::make_shared<Arc>(vertex2, vertex3, std::nullopt, 1, 8);
  const auto arc3 =
      std::make_shared<Arc>(vertex3, vertex1, std::nullopt, 1, 32);

  graph.arcs_.push_back(arc1);
  graph.arcs_.push_back(arc2);
  graph.arcs_.push_back(arc3);

  EXPECT_EQ(graph.total_cost(), 42);
}
