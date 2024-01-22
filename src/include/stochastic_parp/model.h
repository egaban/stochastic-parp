#pragma once

#include <stochastic_parp/instance.h>

#include <unordered_map>

class GRBEnv;
class GRBVar;
class GRBModel;

class Solution {};

class Model {
 private:
  std::unique_ptr<GRBEnv> env_;
  std::unique_ptr<GRBModel> model_;
  std::shared_ptr<Instance> instance_;
  std::unordered_map<Arc, GRBVar> arc_to_variable_;

 public:
  explicit Model(std::shared_ptr<Instance> instance);
  Model(const Model &) = delete;
  Model(Model &&) = delete;

  ~Model();

  Model &operator=(const Model &) = delete;
  Model &operator=(Model &&) = delete;

  void Solve();

 private:
  void CreateAllVariables();

  void CreateAllConstraints();
  void CreateContinuityConstraints();

  // TODO: Think in a budget. For now using 5% of total of arcs.
  void CreateMaxBudgetConstraint();
};
