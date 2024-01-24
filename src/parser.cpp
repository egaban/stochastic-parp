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

std::shared_ptr<Instance> Parser::ParseFile() {
  auto result = this->ParseHeader();
  this->ParseVertices(result);
  this->ParseArcs(result);
  return std::make_shared<Instance>(std::move(result));
}

std::vector<std::string> Parser::SplitWhitespace(const std::string& line) {
  std::istringstream iss{line};

  std::vector<std::string> result;
  for (std::string s; iss >> s;) {
    result.emplace_back(s);
  }

  return result;
}

std::vector<int> Parser::ParseBlocks(const std::string& line) {
  std::istringstream iss{line};

  std::vector<int> result;
  for (std::string s; std::getline(iss, s, ',');) {
    result.emplace_back(std::stoi(s));
  }

  return result;
}

Instance Parser::ParseHeader() {
  SPDLOG_TRACE("Parsing header");
  std::string line;
  std::getline(this->iss_, line);

  auto split = SplitWhitespace(line);

  this->num_vertices_ = std::stoi(split[0]);
  this->num_arcs_ = std::stoi(split[1]);
  this->num_blocks_ = std::stoi(split[2]);

  SPDLOG_INFO("Instance has {} vertices, {} arcs and {} blocks",
              this->num_vertices_, this->num_arcs_, this->num_blocks_);

  return Instance{this->num_vertices_, this->num_arcs_, this->num_blocks_};
}

void Parser::ParseVertices(Instance& instance) {
  SPDLOG_TRACE("Parsing vertices");
  for (auto i = 0; i < this->num_vertices_; ++i) {
    std::string line;
    std::getline(this->iss_, line);
    auto split = SplitWhitespace(line);
    SPDLOG_TRACE("Parsing vertex {}", i);
    auto n = split[0];
    assert(n == "N");

    auto id = std::stoi(split[1]);
    assert(id < instance.graph().num_vertices());

    SPDLOG_TRACE("Vertex {} has blocks {}", i, split[4]);
    for (auto block_num : Parser::ParseBlocks(split[4])) {
      if (block_num < 0) {
        continue;
      }
      assert(block_num < instance.blocks().size());

      auto vertex = instance.graph().vertices_[id];
      auto block = instance.blocks_[block_num];

      vertex->blocks_.emplace_back(block);
      block->vertices_.emplace_back(vertex);
    }
  }
}

void Parser::ParseArcs(Instance& instance) {
  SPDLOG_TRACE("Parsing arcs...");
  for (auto i = 0; i < this->num_arcs_; ++i) {
    std::string line;
    std::getline(this->iss_, line);
    auto split = SplitWhitespace(line);
    SPDLOG_TRACE("Parsing arc {}", i);
    auto n = split[0];
    assert(n == "A");

    const auto from_num = std::stoi(split[1]);
    assert(from_num < instance.graph().num_vertices());
    auto from = instance.graph().vertices_[from_num];

    const auto to_num = std::stoi(split[2]);
    assert(to_num < instance.graph().num_vertices());
    auto to = instance.graph().vertices_[to_num];

    auto size = std::stod(split[3]);
    auto profit = std::stoi(split[5]);
    const auto block_num = std::stoi(split[4]);

    auto block = std::optional<std::weak_ptr<Block>>{};
    if (block_num >= 0) {
      assert(block_num < instance.blocks().size());
      block = std::make_optional(instance.blocks_[block_num]);
    }

    auto arc = std::make_shared<Arc>(from, to, block, profit, i, size);
    instance.graph_.AddArc(arc);
  }
}
