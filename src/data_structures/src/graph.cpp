#include <data_structures/graph.h>
#include <spdlog/spdlog.h>

#include <utility>

Vertex::Vertex(int id) : id_(id), incoming_arcs_(), outgoing_arcs_() {}

Arc::Arc(std::weak_ptr<Vertex> from, std::weak_ptr<Vertex> to,
         std::optional<std::weak_ptr<Block>> block, int profit, int id,
         double size)
    : from_(std::move(from)),
      to_(std::move(to)),
      block_(std::move(block)),
      profit_(profit),
      id_{id},
      size_(size) {}

Graph::Graph(int num_vertices) {
  spdlog::trace("Creating graph with {} vertices", num_vertices);
  vertices_.reserve(num_vertices);
  for (int i = 0; i < num_vertices; ++i) {
    vertices_.push_back(std::make_shared<Vertex>(i));
  }
}

void Graph::AddArc(std::shared_ptr<Arc> arc) {
  this->arcs_.push_back(arc);
  this->vertices_[arc->from_id()]->outgoing_arcs_.push_back(arc);
  this->vertices_[arc->to_id()]->incoming_arcs_.push_back(arc);
}

std::vector<std::shared_ptr<Arc>> Graph::OutgoingCutOf(
    std::set<int> cut_vertices_ids) const {
  std::vector<std::shared_ptr<Arc>> result;

  for (const auto vertex_id : cut_vertices_ids) {
    auto vertex = this->vertices_[vertex_id];

    for (const auto& arc_weak_ptr : vertex->outgoing_arcs()) {
      auto arc = arc_weak_ptr.lock();
      int arc_destination_id = arc->to_id();
      if (!cut_vertices_ids.contains(arc_destination_id)) {
        result.push_back(arc);
      }
    }
  }

  return result;
}
