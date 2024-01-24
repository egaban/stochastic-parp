#pragma once

#include <stochastic_parp/instance.h>

class Solution {
 private:
  double objective_{0};
  std::vector<Arc> arcs_;
  std::shared_ptr<Instance> instance_;

 public:
  friend class Model;

  Solution(std::shared_ptr<Instance> instance)
      : instance_{std::move(instance)} {}

  [[nodiscard]] auto objective() const { return objective_; }
  [[nodiscard]] const auto &arcs() const { return arcs_; }

  void CheckConnectivity() const;

 private:
  void AddArc(Arc arc);
};
