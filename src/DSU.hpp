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
    std::vector<int> fa;///< 父亲节点是谁
    std::vector<int> sz;///< 以编号 i 为父亲的并查集大小
    DSU() {}
    DSU(int n) {
        init(n);
    }
    /**
    * @brief 初始化大小为 n 的并查集
    * @param[in] n 并查集容量，可以使用的节点为 (0<=i<n)
    * @return 返回值 无
    */
    void init(int n) {
        //将 fa 的大小改为 n
        fa.resize(n);
        //fa 的值设置为 1,2,...,n-1。
        std::iota(fa.begin(), fa.end(), 0);
        //所有的并查集的大小都是 1
        sz.assign(n, 1);
    }

    /**
    * @brief 查找节点 x 所属并查集根节点
    * @pre 必须在并查集初始化后才能调用
    * @param[in] x 查找节点编号 (0<=x<n)
    * @return 返回值 x 所属并查集根节点
    */
    int find(int x) {
        if (fa[x] != x) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }

    /**
    * @brief 判断节点 x 和节点 y 是否属于相同并查集
    * @pre 必须在并查集初始化后才能调用
    * @param[in] x 查找节点编号 (0<=x<n)
    * @param[in] y 查找节点编号 (0<=x<n)
    * @return 返回值 true 表示属于相同并查集；false 不是
    */
    bool same(int x, int y) {
        return find(x) == find(y);
    }

    /**
    * @brief 将节点 y 所属的并查集合并到节点 x 所属的并查集
    * @pre 必须在并查集初始化后才能调用
    * @param[in] x 查找节点编号 (0<=x<n)
    * @param[in] y 查找节点编号 (0<=x<n)
    * @return 返回值 true 表示合并成功；false 两者已经是同一个并查集
    */
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

    /**
    * @brief 获得节点 x 所属的并查集内元素数量
    * @pre 必须在并查集初始化后才能调用
    * @param[in] x 节点编号 (0<=x<n)
    * @return 返回值 节点 x 所属的并查集内元素数量
    */
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