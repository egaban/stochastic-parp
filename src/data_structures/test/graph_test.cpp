#define private public
#include <data_structures/graph.h>
#undef private

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

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

  const auto arc1 =
      std::make_shared<Arc>(vertex1, vertex2, std::nullopt, 1, 0, 2);
  const auto arc2 =
      std::make_shared<Arc>(vertex2, vertex3, std::nullopt, 1, 1, 8);
  const auto arc3 =
      std::make_shared<Arc>(vertex3, vertex1, std::nullopt, 1, 2, 32);

  graph.arcs_.push_back(arc1);
  graph.arcs_.push_back(arc2);
  graph.arcs_.push_back(arc3);

  EXPECT_EQ(graph.total_cost(), 42);
}

TEST(GraphTest, OutgoingCut) {
  auto graph = Graph(4);

  const auto vertex1 = graph.vertices_[0];
  const auto vertex2 = graph.vertices_[1];
  const auto vertex3 = graph.vertices_[2];
  const auto vertex4 = graph.vertices_[3];

  const auto arc1 =
      std::make_shared<Arc>(vertex1, vertex2, std::nullopt, 1, 0, 1);
  const auto arc2 =
      std::make_shared<Arc>(vertex1, vertex4, std::nullopt, 1, 1, 1);
  const auto arc3 =
      std::make_shared<Arc>(vertex2, vertex3, std::nullopt, 1, 2, 1);
  const auto arc4 =
      std::make_shared<Arc>(vertex2, vertex4, std::nullopt, 1, 3, 1);
  const auto arc5 =
      std::make_shared<Arc>(vertex3, vertex4, std::nullopt, 1, 4, 1);

  graph.AddArc(arc1);
  graph.AddArc(arc2);
  graph.AddArc(arc3);
  graph.AddArc(arc4);
  graph.AddArc(arc5);

  const auto cut = graph.OutgoingCutOf({0, 1});

  for (const auto arc : cut) {
    SPDLOG_WARN("Arc {} -> {}", arc->from_id(), arc->to_id());
  }

  EXPECT_EQ(cut.size(), 3);

  EXPECT_NE(std::find(cut.begin(), cut.end(), arc2), cut.end());
  EXPECT_NE(std::find(cut.begin(), cut.end(), arc3), cut.end());
  EXPECT_NE(std::find(cut.begin(), cut.end(), arc4), cut.end());
}
