#pragma once
#include "../common.hpp"
template<class num_t>
class FenwickTree {
    const int size;
    vector<num_t> tree;
    function<num_t(const num_t&, num_t)> aggregator;

    public:
        FenwickTree(int size, function<num_t(const num_t&, num_t)> aggregator = sum) : size(size), aggregator(aggregator) {
            this->tree.assign(size, 0);
        }

        FenwickTree(vector<num_t> &arr, function<num_t(const num_t&, num_t)> aggregator = sum) : FenwickTree(arr.size(),
                                                                                                    aggregator) {
            for (int i = 0; i < arr.size(); ++i) {
                add(i, arr[i]);
            }
        }

        void add(int idx, num_t delta) {
            for (; idx < size; idx = idx | (idx + 1))
                tree[idx] = aggregator(tree[idx], delta);
        }

        int query(int l, int r) {
            return query(r) - query(l - 1);
        }
        int query(int r) {
            int res = 0;
            for (; r >= 0; r = (r & (r + 1)) - 1) {
                res = aggregator(res, tree[r]);
            }
            return res;
        }
    private:
        static num_t sum(const num_t& a, num_t b) {
            return a + b;
        }
};