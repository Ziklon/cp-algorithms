#pragma once
#include "../common.hpp"

template<class num_t>
class FenwickTree {
    const int size;
    vector<num_t> tree;
    function<num_t(const num_t&, num_t)> aggregator;

    public:
        FenwickTree(int _size, function<num_t(const num_t&, num_t)> _aggregator = sum) : size(_size), aggregator(_aggregator) {
            this->tree.assign(_size, 0);
        }

        FenwickTree(vector<num_t> &arr, function<num_t(const num_t&, num_t)> _aggregator = sum) : FenwickTree(arr.size(),
                                                                                                    _aggregator) {
            for (int i = 0; i < size; ++i) {
                add(i, arr[i]);
            }
        }

        void add(int idx, num_t delta) {
            for (; idx < size; idx = idx | (idx + 1))
                tree[idx] = aggregator(tree[idx], delta);
        }

        num_t query(int l, int r) {
            return query(r) - query(l - 1);
        }
        num_t query(int r) {
            num_t res = 0;
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