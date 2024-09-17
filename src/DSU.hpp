#pragma once

/**
 * @brief 并查集模板
 * @version 1.0.0
 * @date 2024-9-17
 * @author YiZHOU
 * @copydetails 本模板参考金牌选手 JiangLY 的模板
 * 下面的链接是 JiangLY 使用提交
 * https://ac.nowcoder.com/acm/contest/view-submission?submissionId=63239142
 * 下面链接是我自己在CF EDU上验证
 * CF EDU A - Disjoint Sets Union
 *  https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/submission/281566436
 * CF EDU B - Disjoint Sets Union 2
 *  https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/submission/281566933
 */
#include <vector>
#include <cassert>

struct DSU {
    int _n;
    std::vector<int> fa;///< 编号 i 所在并查集根节点是 fa[i]
    std::vector<int> sz;///< 编号 i 所在并查集节点总数
    //如果有额外数据，在这里维护
    std::vector<int> mn;///< 编号 i 所在并查集最小值
    std::vector<int> mx;///< 编号 i 所在并查集最大值
    //如果有额外数据，在这里维护

    DSU():_n(0) {}
    DSU(int n):_n(n) {
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
        //如果有额外数据，在这里维护
        mn.resize(n);
        mx.resize(n);
        for(int i=0;i<n;i++){
            mn[i]=mx[i]=i+1;
        }
        //如果有额外数据，在这里维护
    }

    /**
    * @brief 查找节点 x 所属并查集根节点
    * @pre 必须在并查集初始化后才能调用
    * @param[in] x 查找节点编号 (0<=x<n)
    * @return 返回值 x 所属并查集根节点
    */
    int find(int x) {
        assert(0<=x && x<_n);
        if (fa[x] != x) {
            return fa[x] = find(fa[x]);//路径压缩
            //return find(fa[x]);//不路径压缩。这里需要平均子树大小
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
        assert(0<=x && x<_n);
        assert(0<=y && y<_n);
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
        assert(0<=x && x<_n);
        assert(0<=y && y<_n);
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        //如果有额外数据，在这里维护
        mn[x]=std::min(mn[x],mn[y]);
        mx[x]=std::max(mx[x],mx[y]);
        //如果有额外数据，在这里维护
        sz[x] += sz[y];
        fa[y] = x;
        return true;
    }

    /**
    * @brief 获得节点 x 所属的并查集信息 Info
    * @pre 必须在并查集初始化后才能调用
    * @param[in] x 节点编号 (0<=x<n)
    * @return 返回值 节点 x 所属的并查集信息
    */
    int size(int x) {
        assert(0<=x && x<_n);
        return sz[find(x)];
    }

    //如果有额外数据，在这里维护
    int min(int x){
        assert(0<=x && x<_n);
        return mn[find(x)];
    }
    int max(int x){
        assert(0<=x && x<_n);
        return mx[find(x)];
    }
    //如果有额外数据，在这里维护
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