#include "../common.hpp"

class UnionFind {
    vector<int> parent;
    vector<int> rank;
    int count;
    public:
        UnionFind(int n) : count(n) {
        this->parent.resize(n);
        this->rank.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    int find(int p) {
        while (p != parent[p]) {
            parent[p] = parent[parent[p]];
            p = parent[p];
        }
        return p;
    }

    int size() {
        return count;
    }

    int group_size(int p) {
        return rank[find(p)];
    }

    bool connected(int p, int q) {
        return find(p) == find(q);
    }
    void join(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ){
            return;
        }
        if (rank[rootP] < rank[rootQ]) {
            swap(rootP, rootQ);
        }
        parent[rootQ] = rootP;
        rank[rootP] += rank[rootQ];
        count--;
    }
};