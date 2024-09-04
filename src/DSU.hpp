#pragma once
#include <vector>

struct DSU {
    std::vector<int> id;
    std::vector<int> sz;
    DSU() {}
    DSU(int n) {
        init(n);
    }
    void init(int n) {
        id.resize(n);
        std::iota(id.begin(), id.end(), 0);
        sz.assign(n, 1);
    }
    int find(int x) {
        if (id[x] != x) {
            id[x] = find(id[x]);
        }
        return id[x];
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        sz[x] += sz[y];
        id[y] = x;
        return true;
    }
    int size(int x) {
        return sz[find(x)];
    }
};

/*
 * How to use.
 * 1. define a DSU with n nodes.
 *  DSU dsu(n+1);//I like to use from 1 to n.
 *
 * 2. find the father of x
 *  fa = dsu.find(x);
 *
 * 3. judge x and y are in same DSU
 *  bool ret = dsu.same(x,y);
 *
 * 4. merge x and y
 *   dsu.merge(x,y);
 *
 * 5. get the size of a DSU
 *   int ret = dsu.size(x);
 */