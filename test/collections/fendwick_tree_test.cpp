#include "main/collections/fendwick_tree.hpp"
#include "gtest/gtest.h"

TEST(fenwick_tree_test, SimpleQuery) {
    FenwickTree<int> tree(10);
    tree.add(1, 5);
    EXPECT_EQ(5, tree.query(2));
}