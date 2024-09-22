#pragma once

const int N=1e6+10;

/**
 * Lazy Segment Tree (LGT)
 * 使用数组实现的懒标记线段树，操作范围为 [1, n]
 * 使用方法：
 * 对于每道题，我们需要的有一下3个地方
 *  1. TAG的定义。Tag是所有懒标记的集合。需要根据题目定义懒标记，实现 apply() 函数
 *  2. NODE的定义。NODE是线段树维护的内容。需要根据题目定义内容，实现 apply() 函数
 *  3. 重载 operator+，用于合并左右儿子内容
 *
 */
const int N=1e5+10;
int a[N];//构建线段树的原始数据

int n;//线段树的数量
//懒标记部分
struct Tag {
    //to add 懒标记
    int mul;//乘法
    int add;//加法
    Tag(int mul_=1, int add_=0):mul(mul_),add(add_){}
    // apply 函数提供给 push() 使用
    //用父结点的标记更新儿子的标记
    void apply(const Tag &t) &{
        //todo
        mul = mul * t.mul % P;
        add = (add * t.mul + t.add) % P;//自己的标记加上父亲的标记
    }
}tag[N<<2];

//线段树信息部分
struct NODE {
    int sum;
    NODE(int val=0) : sum(val) {
    }
    //根据懒标记更新儿子的数据
    void apply(const Tag &t, int len){
        sum = (1ll * sum * t.mul + 1ll * t.add * len) % P;
    }
}nod[N<<2];
NODE operator+(const NODE &a, const NODE &b) {
    NODE c;
    // 对 a（左儿子） 和 b（右儿子） 一通操作合成 c（父结点）
    // to do
    c.sum = (a.sum + b.sum) % P;
    return c;
}

//>>>下面的函数是不需要改变的
//上推数据
void pull(int p){
    nod[p] = nod[2*p] + nod[2*p+1];
}
void apply(int u, const Tag &v, int len){
    nod[u].apply(v, len);
    tag[u].apply(v);
}
//下推标志位
void push(int u, int lenL, int lenR) {
    //更新左儿子 [l, m] m-l+1  (r+l)/2
    apply(2*u, tag[u], lenL);
    //更新右儿子
    apply(2*u+1, tag[u], lenR);
    //清理标志
    tag[u]=Tag();
}
void build(int u, int l, int r) {
    if (l==r) {
        nod[u] = NODE(a[l]);
        return;
    }
    int m=(l+r)>>1;
    //操作区间 [l, m]
    build(2*u, l, m);
    //操作区间 [m+1, r]
    build(2*u+1, m+1, r);
    pull(u);
}

//[ql, qr]+val
void update(int u, int l, int r, int ql, int qr, const Tag &val) {
    if (ql<=l && r<=qr) {
        apply(u, val, r-l+1);
        return;
    }
    //就是这句话，将时间复杂度从 nlogn 平均变成 logn
    int m=(l+r)>>1;
    push(u, m-l+1, r-m);//标志位下推
    //[l,m]
    if (ql<=m) {
        update(2*u, l, m, ql, qr, val);
    }
    //[m+1,r]
    if (m<qr) {
        update(2*u+1, m+1, r, ql, qr, val);
    }
    pull(u);
}
void update(int ql, int qr, const Tag &val) {
    update(1,1,n,ql,qr,val);
}

NODE query(int u, int l, int r, int ql, int qr) {
    if (ql<=l && r<=qr) {
        return nod[u];
    }
    NODE t1,t2;
    int m=(l+r)>>1;
    push(u, m-l+1, r-m);//标志位下推
    //[l,m]
    if (ql<=m) {
        t1=query(2*u, l, m, ql, qr);
    }
    //[m+1, r]
    if (m<qr) {
        t2=query(2*u+1, m+1, r, ql, qr);
    }
    return t1+t2;
}
NODE query(int ql, int qr) {
    return query(1,1,n,ql,qr);
}