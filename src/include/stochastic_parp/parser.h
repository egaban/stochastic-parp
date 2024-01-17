#pragma once

#include <stochastic_parp/instance.h>

#include <fstream>

class Parser {
 private:
  std::ifstream iss_;
  int num_arcs_ = 0;
  int num_vertices_ = 0;
  int num_blocks_ = 0;

 public:
  explicit Parser(const char* filename);

  [[nodiscard]] Instance ParseFile();

 private:
  [[nodiscard]] Instance ParseHeader();

  /**
   * Splits a string into a vector of string views, using whitespace characters
   * as the delimiter.
   * */
  [[nodiscard]] static std::vector<std::string> SplitWhitespace(
      const std::string& line);
};
