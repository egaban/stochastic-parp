#include <spdlog/spdlog.h>
#include <stochastic_parp/config.h>

#include <toml++/toml.hpp>

Config::Config(const char* filename) {
  try {
    auto table = toml::parse_file(filename);
    log_level_ = table["log_level"].value_or(log_level_);
    write_model_ = table["debug"]["write_model"].value_or(false);
  } catch (const toml::parse_error& err) {
    SPDLOG_CRITICAL("Failed to parse config file: {}", err.what());
  }
}

const std::string& Config::GetLogLevel() { return Get().log_level_; }

bool Config::write_model() { return Get().write_model_; }
