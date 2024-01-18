#pragma once

#include <memory>
#include <optional>
#include <vector>

class Arc;
class Block;

class Vertex {
 private:
  std::vector<std::weak_ptr<Arc>> incoming_arcs_;
  std::vector<std::weak_ptr<Arc>> outgoing_arcs_;
  std::vector<std::weak_ptr<Block>> blocks_;

  friend class Parser;

 public:
  Vertex();
};

class Arc {
 private:
  std::weak_ptr<Vertex> from_;
  std::weak_ptr<Vertex> to_;
  std::optional<std::weak_ptr<Block>> block_;
  int profit_;
  double size_;

  friend class Parser;

 public:
  Arc(std::weak_ptr<Vertex> from, std::weak_ptr<Vertex> to,
      std::optional<std::weak_ptr<Block>> block, int profit, double size);

  [[nodiscard]] const auto& from() const { return from_; }
  [[nodiscard]] const auto& to() const { return to_; }
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
