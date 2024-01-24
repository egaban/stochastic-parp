#include <gurobi_c++.h>
#include <spdlog/spdlog.h>
#include <stochastic_parp/config.h>
#include <stochastic_parp/model.h>

#include <utility>

class ConnectivityCallback : public GRBCallback {
 private:
  const Model* model_;

 public:
  ConnectivityCallback(const Model* model) : model_{model} {}

 protected:
  void callback() override {
    if (where == GRB_CB_MIPSOL) {
    }
  };
};

Model::Model(std::shared_ptr<Instance> instance)
    : env_{std::make_unique<GRBEnv>()},
      model_{std::make_unique<GRBModel>(*env_)},
      instance_{std::move(instance)} {
  SPDLOG_INFO("Creating the model");
  try {
    model_->set(GRB_IntParam_LazyConstraints, 1);
    model_->set(GRB_IntAttr_ModelSense, GRB_MAXIMIZE);

    this->CreateAllVariables();
    this->CreateAllConstraints();

    if (Config::write_model()) {
      auto filename = "model.lp";
      SPDLOG_INFO("Writing model file {}", filename);
      this->model_->write(filename);
    }
  } catch (GRBException e) {
    SPDLOG_CRITICAL(e.getMessage());
  }
}

void Model::CreateAllVariables() {
  SPDLOG_DEBUG("Creating variables...");
  for (const auto& arc : this->instance_->graph().arcs()) {
    auto var = this->model_->addVar(0.0, 1.0, arc->profit(), GRB_BINARY,
                                    arc->variable_name());
    this->arc_to_variable_.emplace(*arc, var);
  }
}

void Model::CreateAllConstraints() {
  SPDLOG_DEBUG("Creating constraints...");
  this->CreateContinuityConstraints();
  this->CreateMaxBudgetConstraint();
}

void Model::CreateContinuityConstraints() {
  SPDLOG_DEBUG("Creating continuity constraints");
  for (const auto& vertex : this->instance_->graph().vertices()) {
    GRBLinExpr incoming, outgoing;
    for (const auto& arc : vertex->outgoing_arcs()) {
      outgoing += this->arc_to_variable_.at(*arc.lock());
    }
    for (const auto& arc : vertex->incoming_arcs()) {
      incoming += this->arc_to_variable_.at(*arc.lock());
    }

    auto name = std::format("continuity_{}", vertex->id());
    this->model_->addConstr(incoming, GRB_EQUAL, outgoing, std::move(name));
  }
}

void Model::CreateMaxBudgetConstraint() {
  SPDLOG_DEBUG("Creating budget constraint");
  GRBLinExpr budget_expr;
  for (const auto& arc : this->instance_->graph().arcs()) {
    budget_expr += arc->cost() * this->arc_to_variable_.at(*arc);
  }

  auto budget = static_cast<double>(this->instance_->graph().total_cost()) *
                Config::arcs_budget();
  SPDLOG_DEBUG("Budget: {}", budget);
  this->model_->addConstr(budget_expr, GRB_LESS_EQUAL, budget, "budget");
}

std::optional<Solution> Model::Solve() {
  SPDLOG_INFO("Solving the model");

  auto callback = ConnectivityCallback{this};

  this->model_->setCallback(&callback);
  this->model_->optimize();

  // if (this->model_->get(GRB_IntAttr_Status) == GRB_OPTIMAL) {
  //   SPDLOG_INFO("Model solved to optimality");
  //
  //   Solution solution;
  //   for (const auto& [arc, var] : this->arc_to_variable_) {
  //     if (var.get(GRB_DoubleAttr_X) > 0.5) {
  //       solution.AddArc(arc);
  //     }
  //   }
  // } else if (this->model_->get(GRB_IntAttr_Status) == GRB_INFEASIBLE) {
  //   SPDLOG_INFO("Model is infeasible");
  // } else {
  //   SPDLOG_INFO("Model is infeasible or unbounded");
  // }

  return std::nullopt;
}

Model::~Model() = default;
