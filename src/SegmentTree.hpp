#pragma once

/**
 * @brief 普通线段树
 * @version 1.0.0
 * @date 2024-9-20
 * @author YiZHOU
 * @copydetails 本模板参考金牌选手 JiangLY 的模板
 * 下面的链接是 JiangLY 使用提交
 *      https://codeforces.com/contest/1672/problem/H   https://codeforces.com/contest/1672/submission/154766851
 * 下面是我自己的提交
 *      题目                                              代码
 *      https://www.spoj.com/problems/GSS1/             https://paste.ubuntu.com/p/8yrdw83zRN/
 */
#include<functional>
#include<cassert>
#include<vector>

struct Info {
    //to add 根据题目定义需要维护的数据
    //本例我们维护：和，最大值
    int sum;//和
    int mx;//最大值
    //缺省构造函数
    Info(){
        //to add
        sum = 0;
        mx  = -INF;
    }
    //带参数构造函数
    Info(int val){
        //to add
        sum = mx =val;
    }
};
Info operator+(Info a, Info b) {
    Info c;
    // 对 a（左儿子） 和 b（右儿子） 一通操作合成 c（父结点）
    // to do
    c.sum = a.sum + b.sum;
    c.mx  = std::max(a.mx, b.mx);
    return c;
}

//普通线段树
template<class Info,
        class Merge = std::plus<Info>>
struct SegmentTree {
    const int n;
    const Merge merge;
    std::vector<Info> info;
    SegmentTree(int n) : n(n), merge(Merge()), info(4 << std::__lg(n)) {}
    SegmentTree(std::vector<Info> init) : SegmentTree(init.size()) {
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            //操作区间为 [l, r)
            if (r - l == 1) {
                info[p] = init[l];
                return;
            }
            int m = (l + r) / 2;
            //操作区间为 [l, m)
            build(2 * p, l, m);
            //操作区间为 [m, r)
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        info[p] = merge(info[2 * p], info[2 * p + 1]);
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        //操作区间为 [l, r)
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        //操作区间为 [l, r)
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        //操作区间为 [l, r)
        if (l >= y || r <= x) {
            //处于非法区间
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return merge(rangeQuery(2 * p, l, m, x, y), rangeQuery(2 * p + 1, m, r, x, y));
    }
    Info rangeQuery(int l, int r) {
        //操作区间为 [l, r)
        return rangeQuery(1, 0, n, l, r);
    }
};
