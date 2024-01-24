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

  [[nodiscard]] int Count() {
    int result = 0;

    for (int i = 0; i < parent_.size(); i++) {
      if (Find(i) == i) {
        result++;
      }
    }

    return result;
  }

  /**
   * Returns the parent of a smallest set that has size >= 2.
   */
  [[nodiscard]] int SmallestConnectedSet() {
    int result = -1;
    int smallest_component_size = INT_MAX;

    for (int i = 0; i < parent_.size(); i++) {
      auto parent = Find(i);
      auto size = size_[parent];
      if (size >= 2 && size < smallest_component_size) {
        result = parent;
        smallest_component_size = size;
      }
    }

    if (result == -1) {
      SPDLOG_ERROR("Every component has size 1.");
    }

    return result;
  }

  [[nodiscard]] int Size(int n) {
    int parent = Find(n);
    return size_[parent];
  }

  [[nodiscard]] std::vector<int> SetOf(int n) {
    std::vector<int> result;

    for (int i = 0; i < parent_.size(); i++) {
      if (Find(i) == Find(n)) {
        result.push_back(i);
      }
    }

    return result;
  }

 private:
  std::vector<int> parent_;
  std::vector<int> size_;
  std::vector<int> rank_;
};
