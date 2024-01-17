#pragma once

#include <data_structures/graph.h>

class Instance {
 private:
  Graph graph_;
  int num_arcs_;
  int num_blocks_;

 public:
  Instance(int num_vertices, int num_arcs, int num_blocks)
      : graph_(num_vertices), num_arcs_(num_arcs), num_blocks_(num_blocks) {}

  [[nodiscard]] const auto& graph() const { return graph_; }
  [[nodiscard]] auto num_arcs() const { return num_arcs_; }
  [[nodiscard]] auto num_blocks() const { return num_blocks_; }
};
