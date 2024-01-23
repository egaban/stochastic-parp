#pragma once

#include <spdlog/spdlog.h>

#include <numeric>
#include <vector>

class UnionFind {
 public:
  UnionFind(int n) : parent_(n), size_(n, 1), rank_(n, 0) {
    std::iota(parent_.begin(), parent_.end(), 0);
  }

  [[nodiscard]] int Find(int x) {
    assert(x < parent_.size());
    if (parent_[x] != x) {
      parent_[x] = Find(parent_[x]);
    }
    return parent_[x];
  }

  void Union(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (x == y) {
      SPDLOG_WARN("UnionFind: Trying to merge two nodes in the same set.");
      return;
    }

    if (rank_[x] < rank_[y]) {
      std::swap(x, y);
    }

    parent_[y] = x;
    size_[x] += size_[y];

    if (rank_[x] == rank_[y]) {
      rank_[x]++;
    }
  }

 private:
  std::vector<int> parent_;
  std::vector<int> size_;
  std::vector<int> rank_;
};
