#include <spdlog/spdlog.h>
#include <stochastic_parp/parser.h>

#include <fstream>
#include <sstream>
#include <string>

static Graph parse_file(std::ifstream& file);
static Graph parse_header(std::ifstream& file);

/**
 * Splits a string into a vector of string views, using whitespace characters
 * as the delimiter.
 * */
static auto split_whitespace(const std::string& line) {
  std::istringstream iss{line};

  std::vector<std::string> result;
  for (std::string s; iss >> s;) {
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
