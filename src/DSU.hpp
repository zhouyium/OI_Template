#pragma once
#include <vector>

/**
 * @brief 并查集模板
 * @version 1.0.0
 * @date 2024-9-17
 * @author YiZHOU
 * @copydetails 本模板参考金牌选手 JiangLY 的模板
 * 下面的链接是 JiangLY 使用提交
 * https://ac.nowcoder.com/acm/contest/view-submission?submissionId=63239142
 */
struct DSU {
    std::vector<int> fa;//父亲节点是谁
    std::vector<int> sz;//以编号 i 为父亲的并查集大小
    DSU() {}
    DSU(int n) {
        init(n);
    }
    vofa init(int n) {
        fa.resize(n);
        std::iota(fa.begin(), fa.end(), 0);
        sz.assign(n, 1);
    }
    int find(int x) {
        if (fa[x] != x) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
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
        fa[y] = x;
        return true;
    }
    int size(int x) {
        return sz[find(x)];
    }
};

/*
 * How to use.
 * 1. define a DSU with n nodes.
 *  DSU dsu(n);//由于使用vector，题目节点编号为 1~n，使用的时候是 0~n-1
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