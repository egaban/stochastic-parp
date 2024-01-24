#include <gtest/gtest.h>

#define private public
#include <data_structures/unionfind.h>
#undef private

TEST(UnionFindTest, Parent) {
  const auto uf = UnionFind(3);

  EXPECT_EQ(uf.parent_[0], 0);
  EXPECT_EQ(uf.parent_[1], 1);
  EXPECT_EQ(uf.parent_[2], 2);
}

TEST(UnionFindTest, Rank) {
  const auto uf = UnionFind(3);

  EXPECT_EQ(uf.rank_[0], 0);
  EXPECT_EQ(uf.rank_[1], 0);
  EXPECT_EQ(uf.rank_[2], 0);
}

TEST(UnionFindTest, Size) {
  auto uf = UnionFind(5);

  EXPECT_EQ(uf.size_[0], 1);
  EXPECT_EQ(uf.size_[1], 1);
  EXPECT_EQ(uf.size_[2], 1);

  uf.Union(0, 1);

  EXPECT_EQ(uf.Size(0), 2);

  uf.Union(1, 2);

  EXPECT_EQ(uf.Size(1), 3);

  uf.Union(3, 4);

  EXPECT_EQ(uf.Size(3), 2);

  uf.Union(0, 4);

  EXPECT_EQ(uf.Size(0), 5);
}

TEST(UnionFindTest, UnionFind) {
  auto uf = UnionFind(5);

  uf.Union(0, 1);
  uf.Union(1, 2);
  uf.Union(3, 4);

  EXPECT_EQ(uf.Find(0), uf.Find(1));
  EXPECT_EQ(uf.Find(1), uf.Find(2));
  EXPECT_EQ(uf.Find(0), uf.Find(2));
  EXPECT_EQ(uf.Find(3), uf.Find(4));

  EXPECT_NE(uf.Find(3), uf.Find(1));
  EXPECT_NE(uf.Find(2), uf.Find(4));

  uf.Union(0, 4);
  EXPECT_EQ(uf.Find(2), uf.Find(4));
  EXPECT_EQ(uf.Find(3), uf.Find(1));
}

TEST(UnionFindTest, Count) {
  auto uf = UnionFind(5);

  EXPECT_EQ(uf.Count(), 5);

  uf.Union(0, 1);
  uf.Union(1, 2);

  EXPECT_EQ(uf.Count(), 3);

  uf.Union(3, 4);

  EXPECT_EQ(uf.Count(), 2);

  uf.Union(0, 4);

  EXPECT_EQ(uf.Count(), 1);
}

TEST(UnionFindTest, SmallestConnectedSet) {
  auto uf = UnionFind(5);

  uf.Union(0, 1);

  auto smallest = uf.SmallestConnectedSet();
  EXPECT_EQ(smallest, uf.Find(0));
  EXPECT_EQ(uf.Size(smallest), 2);

  uf.Union(1, 2);

  smallest = uf.SmallestConnectedSet();
  EXPECT_EQ(smallest, uf.Find(1));
  EXPECT_EQ(uf.Size(smallest), 3);

  uf.Union(3, 4);

  smallest = uf.SmallestConnectedSet();
  EXPECT_EQ(smallest, uf.Find(3));
  EXPECT_EQ(uf.Size(smallest), 2);

  uf.Union(0, 4);

  smallest = uf.SmallestConnectedSet();
  EXPECT_EQ(smallest, uf.Find(0));
  EXPECT_EQ(uf.Size(smallest), 5);
}

TEST(UnionFindTest, SetOf) {
  auto uf = UnionFind(5);

  uf.Union(0, 1);
  uf.Union(1, 2);
  uf.Union(3, 4);

  auto set = uf.SetOf(0);
  EXPECT_EQ(set.size(), 3);
  EXPECT_EQ(set[0], 0);
  EXPECT_EQ(set[1], 1);
  EXPECT_EQ(set[2], 2);

  set = uf.SetOf(3);
  EXPECT_EQ(set.size(), 2);
  EXPECT_EQ(set[0], 3);
  EXPECT_EQ(set[1], 4);
}
