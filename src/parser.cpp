#include <spdlog/spdlog.h>
#include <stochastic_parp/parser.h>

#include <fstream>
#include <ranges>
#include <string>

static Graph parse_file(std::ifstream& file);
static Graph parse_header(std::ifstream& file);

/**
 * Splits a string into a vector of string views, using whitespace as the
 * delimiter. Note that this returns a string view, so you cannot use the
 * result after the original string has been destroyed.
 */
static auto split_whitespace(const std::string& line) {
  auto split = line | std::ranges::views::split(' ');

  std::vector<std::string_view> result;
  for (auto&& s : split) {
    result.emplace_back(s);
  }
  return result;
}

Graph read_file(const char* filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    SPDLOG_CRITICAL("Failed to open file {}.", filename);
    exit(1);
  }

  return parse_file(file);
}

Graph parse_file(std::ifstream& file) {
  auto result = parse_header(file);
  return result;
}

Graph parse_header(std::ifstream& file) {
  // std::string line;
  // std::getline(file, line);
}
