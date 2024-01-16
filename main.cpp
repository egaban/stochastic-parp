#include <spdlog/spdlog.h>
#include <stochastic_parp/parser.h>

#include <toml++/toml.hpp>

int main() {
  auto config = toml::parse_file("config.toml");
  auto title = config["log_level"].value_or("info");

  spdlog::set_level(spdlog::level::from_str(title));

  return 0;
}
