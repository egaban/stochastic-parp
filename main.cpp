#include <spdlog/spdlog.h>
#include <stochastic_parp/config.h>
#include <stochastic_parp/model.h>
#include <stochastic_parp/parser.h>

static void ConfigureLogger();

int main(int argc, char** argv) {
  auto args = std::span(argv, argc);

  ConfigureLogger();
  if (args.size() != 2) {
    spdlog::critical("Usage: {} <instance>", args[0]);
    exit(1);
  }

  auto instance = Parser{args[1]}.ParseFile();
  auto model = Model{instance};

  model.Solve();

  return 0;
}

void ConfigureLogger() {
  auto level = spdlog::level::from_str(Config::GetLogLevel());
  spdlog::set_level(level);
  spdlog::set_pattern("%^[%l]%$ %v");
}
