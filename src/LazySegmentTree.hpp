#pragma once

/**
 * @brief 懒标记线段树
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

//懒标记部分
struct Tag {
    //to add 懒标记
    int add;//加法
    Tag(int add_=0):add(add_){}
    // apply 函数提供给 push() 使用
    //用父结点的标记更新儿子的标记
    void apply(const Tag &t) &{
        //todo
        add = add + t.add;//自己的标记加上父亲的标记
    }
};

//数据部分
struct Info {
    //to add 根据题目定义需要维护的数据
    //本例我们维护：和
    int sum;//和
    Info(int val = 0) : sum(val){}
    // 用父结点的标记更新儿子存储的信息
    void apply(const Tag &t, int len){
        sum = sum + 1ll * t.add * len;
    }
};
Info operator+(Info a, Info b) {
    Info c;
    // 对 a（左儿子） 和 b（右儿子） 一通操作合成 c（父结点）
    // to do
    c.sum = a.sum + b.sum;
    return c;
}

//懒标记线段树
template<class Info, class Tag>
struct LazySegmentTree{
    int n;
    std::vector<Info> info; //< 数据
    std::vector<Tag> tag;   //< 懒标记
    LazySegmentTree() : n(0){}
    LazySegmentTree(int n_) : n(n_), info(4 << std::__lg(n)), tag(4 << std::__lg(n)){}
    template<class T>
    LazySegmentTree(std::vector<T> init_) {
        init(init_);
    }
    template<class T>
    void init(std::vector<T> init_){
        n = init_.size();
        info.assign(4 << std::__lg(n), Info());
        tag.assign(4 << std::__lg(n), Tag());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            //操作区间为 [l, r)
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) >> 1;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);

    }
    //> 上传
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    //> 标记下传
    void apply(int p, const Tag &v, int len){
        info[p].apply(v, len);
        tag[p].apply(v);
    }
    void push(int p, int len) {
        apply(2 * p, tag[p], len >> 1);
        apply(2 * p + 1, tag[p], len - (len >> 1));
        tag[p] = Tag();
    }

    //> 单点修改
    void modify(int p, int l, int r, int x, const Info &v) {
        //操作区间为 [l, r)
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) >> 1;
        push(p, r - l);
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

    //> 区域查询
    Info rangeQuery(int p, int l, int r, int x, int y) {
        //操作区间为 [l, r)
        if (l >= y || r <= x) {
            //处于非法区间
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) >> 1;
        push(p, r - l);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        //操作区间为 [l, r)
        return rangeQuery(1, 0, n, l, r);
    }

    //>区域更新
    void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
        //操作区间为 [l, r)
        if (l >= y || r <= x) {
            //处于非法区间
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v, r - l);
            return;
        }
        int m = (l + r) >> 1;
        push(p, r - l);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag &v) {
        //操作区间为 [l, r)
        return rangeApply(1, 0, n, l, r, v);
    }

    //下面的暂时不知道怎么使用，后面再研究
    template<class F>
    int findFirst(int p, int l, int r, int x, int y, F &&pred) {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) >> 1;
        push(p, r - l);
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findFirst(int l, int r, F &&pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
    template<class F>
    int findLast(int p, int l, int r, int x, int y, F &&pred) {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) >> 1;
        push(p, r - l);
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findLast(int l, int r, F &&pred) {
        return findLast(1, 0, n, l, r, pred);
    }
};//LazySegmentTree
