#pragma once

#include <memory>
#include <vector>

class Arc;

class Vertex {
 private:
  std::vector<std::shared_ptr<Arc>> incoming_arcs_;
  std::vector<std::shared_ptr<Arc>> outgoing_arcs_;

 public:
  Vertex();
};

class Arc {
 private:
  std::shared_ptr<Vertex> from_;
  std::shared_ptr<Vertex> to_;
  int cost_;
  int profit_;

 public:
  Arc(int from, int to, int cost, int profit);

  [[nodiscard]] const auto& from() const { return from_; }
  [[nodiscard]] const auto& to() const { return to_; }
  [[nodiscard]] int cost() const { return cost_; }
  [[nodiscard]] int profit() const {
    return profit_;
    ;
  }
};

class Graph {
 private:
  std::vector<std::shared_ptr<Vertex>> vertices_;
  std::vector<std::shared_ptr<Arc>> arcs_;

  friend class Parser;

 public:
  Graph(int num_vertices);

  [[nodiscard]] size_t num_vertices() const { return vertices_.size(); }
  [[nodiscard]] size_t num_arcs() const { return arcs_.size(); }

  [[nodiscard]] const auto& vertices() const { return vertices_; }
};
