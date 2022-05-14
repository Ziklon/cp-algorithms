#pragma once

#include "../common.hpp"

template<typename num_t>
class SegmentTree {
    protected:
        const int size;
        function<num_t(const num_t&, num_t)> joinValue;
        function<num_t(const num_t&, num_t)> accumulate;
        const num_t infinite;
        vector<num_t> tree; 
        
    public:
        SegmentTree(vector<num_t> &arr,
                    const function<num_t(num_t, num_t)> & _joinValue,
                    const function<num_t(num_t, num_t)> & _accumulate,
                    const num_t _infinite) :
            size(sz(arr)),
            joinValue(_joinValue),
            accumulate(_accumulate),
            infinite(_infinite){
            #ifdef LOCAL
                assert(size);
            #endif
            this->tree = vector<num_t>(size * 4);
            build(0, 0, size - 1, arr);
        }

        SegmentTree(int _size,
                    const function<num_t(const num_t&, num_t)> & _joinValue,
                    const function<num_t(const num_t&, num_t)> & _accumulate,
                    const num_t _infinite):
                    size(_size),
                    joinValue(_joinValue),
                    accumulate(_accumulate),
                    infinite(_infinite){
            this-> tree = vector<num_t>(_size * 4);
        } 

        num_t query(int start, int end) {
            #ifdef LOCAL
                assert(start <= end && start >= 0 && end < size);
            #endif
            return query(0, 0, size - 1, start, end);
        }
        
        void update(int at, num_t val) {
            #ifdef LOCAL
            assert(at >= 0 && at < size);
            #endif
            update(0, 0, size - 1, at, val);
        }
        void build(vector<num_t> &arr) {
            build(0,0, size - 1, arr);
        }
        void build(num_t initValue) {
            vector<num_t> arr(size, initValue);
            build(arr);
        }
        
    private:
        void build(int node, int start, int end, vector<num_t> &arr) {
            if (start == end) {
                tree[node] = arr[start];
                return;
            }
            int mid = (start + end) / 2;
            build(2 * node + 1, start, mid, arr);
            build(2 * node + 2, mid + 1, end, arr);
            tree[node] = joinValue(tree[2 * node + 1], tree[2 * node + 2]);
        }

        void update(int node, int start, int end, int idx, num_t val) {
            if (start == end) {
                tree[node] = accumulate(tree[node], val);
                return;
            }
            int mid = (start + end) / 2;
            if (idx <= mid) update(2 * node + 1, start, mid, idx, val);
            else update(2 * node + 2, mid + 1, end, idx, val);
            tree[node] = joinValue(tree[2 * node + 1], tree[2 * node + 2]);
        }

        num_t query(int node, int start, int end, int l, int r) {
            if (start > r || end < l) return infinite;
            if (l <= start && end <= r) return tree[node];
            int mid = (start + end) / 2;
            num_t left = query(2 * node + 1, start, mid, l, r);
            num_t right = query(2 * node + 2, mid + 1, end, l, r);
            return joinValue(left, right);
        }
};