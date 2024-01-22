#include <data_structures/graph.h>
#include <spdlog/spdlog.h>

#include <utility>

Vertex::Vertex(int id) : id_(id), incoming_arcs_(), outgoing_arcs_() {}

Arc::Arc(std::weak_ptr<Vertex> from, std::weak_ptr<Vertex> to,
         std::optional<std::weak_ptr<Block>> block, int profit, double size)
    : from_(std::move(from)),
      to_(std::move(to)),
      block_(std::move(block)),
      profit_(profit),
      size_(size) {}

Graph::Graph(int num_vertices) {
  spdlog::trace("Creating graph with {} vertices", num_vertices);
  vertices_.reserve(num_vertices);
  for (int i = 0; i < num_vertices; ++i) {
    vertices_.push_back(std::make_shared<Vertex>(i));
  }
}
