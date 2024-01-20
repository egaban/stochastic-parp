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

  [[nodiscard]] static const std::string& GetLogLevel();

 private:
  std::string log_level_;

  static const auto& Get() {
    const static Config instance{"config.toml"};
    return instance;
  }
};
