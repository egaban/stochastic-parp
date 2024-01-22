#include <gurobi_c++.h>
#include <spdlog/spdlog.h>
#include <stochastic_parp/config.h>
#include <stochastic_parp/model.h>

#include <utility>

#include "gurobi_c.h"

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
    budget_expr += this->arc_to_variable_.at(*arc);
  }

  // TODO: This budget will be changed.
  constexpr double kBudget = 0.05;
  auto budget =
      static_cast<double>(this->instance_->graph().num_arcs()) * kBudget;
  SPDLOG_DEBUG("Budget: {}", budget);
  this->model_->addConstr(budget_expr, GRB_LESS_EQUAL, budget, "budget");
}

void Model::Solve() {
  SPDLOG_INFO("Solving the model");
  this->model_->optimize();
}

Model::~Model() = default;
