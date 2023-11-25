#include <data_structures/graph.h>
#include <spdlog/spdlog.h>

Vertex::Vertex() : incoming_arcs_(), outgoing_arcs_() {}

// Arc::Arc() {
//
// }

Graph::Graph(int num_vertices) {
  spdlog::trace("Creating graph with {} vertices", num_vertices);
  vertices_.reserve(num_vertices);
  for (int i = 0; i < num_vertices; ++i) {
    vertices_.push_back(std::make_shared<Vertex>());
  }
}
