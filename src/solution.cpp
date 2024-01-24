#include <data_structures/unionfind.h>
#include <stochastic_parp/solution.h>

void Solution::AddArc(Arc arc) {
  this->objective_ += arc.profit();
  this->arcs_.push_back(std::move(arc));
}

void Solution::CheckConnectivity() const {
  auto num_vertices = static_cast<int>(this->instance_->graph().num_vertices());
  auto uf = UnionFind{num_vertices};

  for (const auto& arc : this->arcs_) {
    uf.Union(arc.from_id(), arc.to_id());
  }

  auto smallest_component = uf.SetOf(uf.SmallestConnectedSet());
}
