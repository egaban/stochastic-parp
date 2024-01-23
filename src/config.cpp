#include <spdlog/spdlog.h>
#include <stochastic_parp/config.h>

#include <toml++/toml.hpp>

static constexpr std::string kDefaultLogLevel{"info"};
static constexpr bool kDefaultWriteModel{false};
static constexpr double kDefaultArcsBudget{0.1};

Config::Config(const char* filename)
    : log_level_{"info"},
      write_model_{kDefaultWriteModel},
      arcs_budget_{kDefaultArcsBudget} {
  try {
    auto table = toml::parse_file(filename);

    log_level_ = table["log_level"].value_or(kDefaultLogLevel);
    write_model_ = table["debug"]["write_model"].value_or(kDefaultWriteModel);
    arcs_budget_ = table["arcs_budget"].value_or(kDefaultArcsBudget);
  } catch (const toml::parse_error& err) {
    SPDLOG_ERROR("Failed to parse config file: {}", err.what());
  }
}

// const std::string& Config::log_level() { return Get().log_level_; }
//
// bool Config::write_model() { return Get().write_model_; }
//
// double Config::arcs_budget() { return Get().arcs_budget_; }
