#pragma once

#include <format>
#include <memory>
#include <numeric>
#include <optional>
#include <vector>

class Arc;
class Block;

class Vertex {
 private:
  int id_;
  std::vector<std::weak_ptr<Arc>> incoming_arcs_;
  std::vector<std::weak_ptr<Arc>> outgoing_arcs_;
  std::vector<std::weak_ptr<Block>> blocks_;

  friend class Parser;

 public:
  explicit Vertex(int id);

  bool operator==(const Vertex& other) const { return this->id_ == other.id_; }

  [[nodiscard]] auto id() const { return this->id_; }

  [[nodiscard]] const auto& incoming_arcs() const {
    return this->incoming_arcs_;
  }

  [[nodiscard]] const auto& outgoing_arcs() const {
    return this->outgoing_arcs_;
  }
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

  bool operator==(const Arc& other) const {
    return this->to_.lock() == other.to_.lock() &&
           this->from_.lock() == other.from_.lock();
  }

  [[nodiscard]] const auto& from() const { return from_; }
  [[nodiscard]] const auto& to() const { return to_; }
  [[nodiscard]] int profit() const {
    return profit_;
    ;
  }

  [[nodiscard]] auto variable_name() const {
    return std::format("x_{}_{}", from_.lock()->id(), to_.lock()->id());
  }

  [[nodiscard]] auto cost() const { return size_; }
};

class Graph {
 private:
  std::vector<std::shared_ptr<Vertex>> vertices_;
  std::vector<std::shared_ptr<Arc>> arcs_;

  friend class Parser;

 public:
  explicit Graph(int num_vertices);

  [[nodiscard]] size_t num_vertices() const { return vertices_.size(); }
  [[nodiscard]] size_t num_arcs() const { return arcs_.size(); }

  [[nodiscard]] const auto& vertices() const { return this->vertices_; }
  [[nodiscard]] const auto& arcs() const { return this->arcs_; }

  // Returns the total arc cost sum of the graph.
  [[nodiscard]] double total_cost() const {
    return std::accumulate(
        arcs_.begin(), arcs_.end(), 0.0,
        [](int sum, const auto& arc) { return sum + arc->cost(); });
  }
};

template <>
struct std::hash<Arc> {
  std::size_t operator()(const Arc& arc) const noexcept {
    return std::hash<std::string>{}(arc.variable_name());
  }
};
