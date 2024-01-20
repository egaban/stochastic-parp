#include <spdlog/spdlog.h>
#include <stochastic_parp/config.h>

#include <toml++/toml.hpp>

Config::Config(const char* filename) : log_level_{"info"} {
  try {
    auto table = toml::parse_file(filename);
    log_level_ = table["log_level"].value_or(log_level_);
  } catch (const toml::parse_error& err) {
    SPDLOG_CRITICAL("Failed to parse config file: {}", err.what());
  }
}

const std::string& Config::GetLogLevel() { return Get().log_level_; }
