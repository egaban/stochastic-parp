#include <spdlog/spdlog.h>
#include <stochastic_parp/parser.h>

#include <fstream>
#include <sstream>
#include <string>

Parser::Parser(const char* filename) : iss_{filename} {
  if (!iss_.is_open()) {
    SPDLOG_CRITICAL("Failed to open file {}.", filename);
    exit(1);
  }
}

Instance Parser::ParseFile() { return this->ParseHeader(); }

std::vector<std::string> Parser::SplitWhitespace(const std::string& line) {
  std::istringstream iss{line};

  std::vector<std::string> result;
  for (std::string s; iss >> s;) {
    result.emplace_back(s);
  }

  return result;
}

Instance Parser::ParseHeader() {
  std::string line;
  std::getline(this->iss_, line);

  auto split = SplitWhitespace(line);

  auto num_vertices = std::stoi(split[0]);
  auto num_arcs = std::stoi(split[1]);
  auto num_blocks = std::stoi(split[2]);

  return Instance{num_vertices, num_arcs, num_blocks};
}
