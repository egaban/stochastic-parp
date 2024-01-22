#pragma once

#include <stochastic_parp/instance.h>

#include <fstream>
#include <memory>

class Parser {
 private:
  std::ifstream iss_;
  int num_arcs_ = 0;
  int num_vertices_ = 0;
  int num_blocks_ = 0;

 public:
  explicit Parser(const char* filename);

  [[nodiscard]] std::shared_ptr<Instance> ParseFile();

 private:
  [[nodiscard]] Instance ParseHeader();

  void ParseVertices(Instance& instance);
  void ParseArcs(Instance& instance);

  /**
   * Splits a string into a vector of strings, using whitespace characters
   * as the delimiter.
   * */
  [[nodiscard]] static std::vector<std::string> SplitWhitespace(
      const std::string& line);

  /**
   * Parses the list of blocks (comma-separated) into a vector of ints.
   * */
  [[nodiscard]] static std::vector<int> ParseBlocks(const std::string& line);
};
