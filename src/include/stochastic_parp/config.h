#pragma once

#include <string>

class Config {
 public:
  Config(const char* filename);
  ~Config() = default;

  // Delete the copy constructor and assignment operator so we don't have copies
  // of our Singleton.
  Config(Config const&) = delete;
  void operator=(Config const&) = delete;
  Config(Config&&) = delete;
  Config& operator=(Config&&) = delete;

  [[nodiscard]] static const std::string& log_level() {
    return Get().log_level_;
  }

  [[nodiscard]] static bool write_model() { return Get().write_model_; }

  // Maximum budget: the percentage of the total arcs cost sum.
  [[nodiscard]] static double arcs_budget() { return Get().arcs_budget_; }

 private:
  std::string log_level_;
  bool write_model_;
  double arcs_budget_;

  static const Config& Get() {
    const static Config instance{"config.toml"};
    return instance;
  }
};
