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
  const auto uf = UnionFind(3);

  EXPECT_EQ(uf.size_[0], 1);
  EXPECT_EQ(uf.size_[1], 1);
  EXPECT_EQ(uf.size_[2], 1);
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
