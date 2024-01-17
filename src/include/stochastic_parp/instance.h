#pragma once

#include <data_structures/graph.h>

class Block {
 private:
  int id_;
  std::vector<std::shared_ptr<Vertex>> vertices_;

  friend class Parser;

 public:
  explicit Block(int id) : id_(id) {}

  [[nodiscard]] int id() const { return id_; }
  [[nodiscard]] const auto& vertices() const { return vertices_; }
};

class Instance {
 private:
  Graph graph_;
  std::vector<std::shared_ptr<Block>> blocks_;
  int num_arcs_;

  friend class Parser;

 public:
  Instance(int num_vertices, int num_arcs, int num_blocks)
      : graph_(num_vertices), num_arcs_(num_arcs) {
    for (auto i = 0; i < num_blocks; ++i) {
      blocks_.emplace_back(std::make_shared<Block>(i));
    }
  }

  [[nodiscard]] const auto& graph() const { return graph_; }
  [[nodiscard]] const auto& blocks() const { return blocks_; }
  [[nodiscard]] auto num_arcs() const { return num_arcs_; }
};
