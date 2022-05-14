#include "main/collections/segment_tree.hpp"
#include "gtest/gtest.h"

TEST(segment_tree_test, SimpleQueryAdd) {
    
    auto sum = [&](int x, int y) { return x + y; };
    auto accum = [&](int x, int y) {return x + y; };
    const int N = 20;

    SegmentTree<int> tree(N, sum, accum, 0);
    tree.update(1, 10);
    tree.update(5, 5);
    int ans = tree.query(1, 10);
    EXPECT_EQ(15, ans);
}

TEST(segment_tree_test, SimpleQueryAddWithReplace) {
    
    auto sum = [&](int x, int y) { return x + y; };
    auto accum = [&](int x, int y) {return y; };
    const int N = 20;

    SegmentTree<int> tree(N, sum, accum, 0);
    tree.update(1, 10);
    tree.update(5, 5);
    int ans = tree.query(1, 10);
    EXPECT_EQ(15, ans);

    tree.update(5, 10);
    EXPECT_EQ(20, tree.query(1, 10)); 
}