#pragma once

const int N=1e6+10;

/**
 * Lazy Segment Tree (LGT)
 * 使用数组实现的懒标记线段树，操作范围为 [1, n]
 * 使用方法：
 * 对于每道题，我们需要的有一下3个地方
 *  1. NODE的定义
 *  2. combine函数。用于合并左右儿子。
 *  3. eval函数。处理懒标记等。
 *
 */
struct NODE {
    int l,r;
    int sum;
    int add;//和的懒标志
    NODE() {
        sum=0;
        add=0;
    }
}rt[N<<2];
int a[N];//构建线段树的原始数据

//将t1,t2两个节点数据合并位t
NODE combine(const NODE &t1, const NODE &t2) {
    NODE res;
    res.sum=t1.sum+t2.sum;
    res.l  = min(t1.l, t2.l);
    res.r  = max(t1.r, t2.r);
    return res;
}

//根据add，跟新节点t
void eval(NODE &t, int add) {
    //更新和
    t.sum = t.sum+(t.r-t.l+1)*add;
    //更新懒标志
    if (t.l==t.r) {
        t.add = 0;
    } else {
        t.add = t.add+add;
    }
}

//下面的函数是不需要改变的
void pushdown(int u) {
    //下推标志位
    if (rt[u].add==0) {
        //没有标志
        return;
    }
    //更新左儿子
    eval(rt[2*u], rt[u].add);
    //更新右儿子
    eval(rt[2*u+1], rt[u].add);
    //清理标志
    rt[u].add = 0;
}
void build(int u, int l, int r) {
    rt[u].l=l;
    rt[u].r=r;
    if (l==r) {
        eval(rt[u], a[l]);
        return;
    }
    int m=(l+r)/2;
    //操作区间 [l, m]
    build(2*u, l, m);
    //操作区间 [m+1, r]
    build(2*u+1, m+1, r);
    rt[u]=combine(rt[2*u], rt[2*u+1]);
}

//[ql, qr]+add
void update(int u, int ql, int qr, int add) {
    int l=rt[u].l;
    int r=rt[u].r;
    if (ql<=l && r<=qr) {
        eval(rt[u], add);
        return;
    }
    //就是这句话，将时间复杂度从 nlogn 平均变成 logn
    pushdown(u);//标志位下推
    int m=(l+r)/2;
    //[l,m]
    if (ql<=m) {
        update(2*u, ql, qr, add);
    }
    //[m+1,r]
    if (m<qr) {
        update(2*u+1, ql, qr, add);
    }
    rt[u]=combine(rt[2*u], rt[2*u+1]);
}
NODE query(int u, int ql, int qr) {
    int l=rt[u].l;
    int r=rt[u].r;
    if (ql<=l && r<=qr) {
        return rt[u];
    }
    pushdown(u);
    NODE res,t1,t2;
    int m=(l+r)/2;
    //[l,m]
    if (ql<=m) {
        t1=query(2*u, ql, qr);
    }
    //[m+1, r]
    if (m<qr) {
        t2=query(2*u+1, ql, qr);
    }
    res=combine(t1, t2);
    return res;
}
