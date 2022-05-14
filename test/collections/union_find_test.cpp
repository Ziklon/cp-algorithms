#include "main/collections/union_find.hpp"
#include "gtest/gtest.h"

TEST(union_find_test, Creation) {
    UnionFind uf(5);
    EXPECT_EQ(5, uf.size());
    vector<int> seq(5, 1);
    seq[5]++;
}

TEST(union_find_test, Join) {
    UnionFind uf(5);
    uf.join(0,1);
    EXPECT_EQ(4, uf.size());
    EXPECT_EQ(true, uf.connected(0,1));
    EXPECT_EQ(2, uf.group_size(1));
}