/*
 * https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/A
 */
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
using PLL=pair<LL,LL>;
const LL INF=0x3f3f3f3f3f3f3f3f;
const double EPS=1e-10;

const int N=2e6+10;
template<typename T=long long>
struct SEGNODE{
    //本节点表示的区间范围[l,r]
    int l;
    int r;
    T add;//Lazy tag;
    T sum;//区间和
    T max_sum;//区间最大子段和
    T max_prefix;//区间中，前缀的最大和
    T max_suffix;//区间中，后缀的最大和
    T minx;//最小值
    T maxx;//最大值
    int cnt_min;//最小值数量
    int cnt_max;//最小值数量
    //缺省构造函数
    SEGNODE(){
        l=r=0;
        add=sum=0;
        minx=2e9;
        max_sum=maxx=max_prefix=max_suffix=-2e9;
        cnt_min=1;
        cnt_max=1;
    }
};
template<typename T=long long>
class SEGMENTTREE{
private:
    std::vector<SEGNODE<T>> val;//保存数据

private:
    //将左右儿子合成一个新节点
    void combine(SEGNODE<T> &t, const SEGNODE<T> &t1, const SEGNODE<T> &t2){
        t.sum =t1.sum+t2.sum;
        t.max_sum =max({t1.max_sum, t2.max_sum, t1.max_suffix+t2.max_prefix});
        t.max_prefix = max(t1.max_prefix, t1.sum+t2.max_prefix);
        t.max_suffix = max(t2.max_suffix, t2.sum+t1.max_suffix);
        if(t1.minx<t2.minx){
            t.minx    = t1.minx;
            t.cnt_min = t1.cnt_min;
        }else if(t1.minx>t2.minx){
            t.minx    = t2.minx;
            t.cnt_min = t2.cnt_min;
        }else{
            t.minx    = t1.minx;
            t.cnt_min = t1.cnt_min+t2.cnt_min;
        }
        if(t1.maxx<t2.maxx){
            t.maxx    = t2.maxx;
            t.cnt_max = t2.cnt_max;
        }else if(t1.maxx>t2.maxx){
            t.maxx    = t1.maxx;
            t.cnt_max = t1.cnt_max;
        }else{
            t.maxx    = t1.maxx;
            t.cnt_max = t1.cnt_max+t2.cnt_max;
        }
        t.l   =min(t1.l, t2.l);
        t.r   =max(t1.r, t2.r);
    }

    void eval(SEGNODE<T> &t, T add){
        t.sum = t.sum+(t.r-t.l+1)*add;
        if(add<0){
            t.max_sum=t.max_prefix=t.max_suffix=0;
        }else{
            t.max_sum=t.max_prefix=t.max_suffix=t.sum;
        }
        t.add +=add;//加上懒标记
        if(t.l==t.r){
            //leaf
            t.minx=t.maxx=t.sum;
            t.cnt_min=t.cnt_max=1;
            t.add=0;
        }
    }

    void evalSet(SEGNODE<T> &t, T v){
        t.sum = v;
        if(v<0){
            t.max_sum=t.max_prefix=t.max_suffix=0;
        }else{
            t.max_sum=t.max_prefix=t.max_suffix=t.sum;
        }
        if(t.l==t.r){
            //leaf
            t.minx=t.maxx=t.sum;
            t.cnt_min=t.cnt_max=1;
            t.add=0;
        }
    }

    //下推
    void pushdown(int u){
        if(val[u].add==0){
            return;
        }
        //更新左子树
        eval(val[2*u], val[u].add);
        //更新右儿子
        eval(val[2*u+1], val[u].add);
        //清标记
        val[u].add=0;
    }
public:
    //根据数组创建树
    SEGMENTTREE(const std::vector<T> &vt){
        for(int i=0;i<=4*vt.size();i++){
            val.push_back(SEGNODE<T>());
        }
        build(1,1,vt.size(),vt);
    }

    void build(int u, int l, int r,const std::vector<T> &vt){
        val[u].l=l;
        val[u].r=r;
        if(l==r){
            eval(val[u], vt[l-1]);
            return;
        }
        int m=(l+r)>>1;
        build(2*u,l,m,vt);
        build(2*u+1,m+1,r,vt);
        combine(val[u], val[2*u], val[2*u+1]);
    }

    SEGNODE<T> query(int u, int ql, int qr){
        int l=val[u].l;
        int r=val[u].r;
        if(ql<=l && r<=qr){
            return val[u];
        }
        pushdown(u);

        SEGNODE<T> res, t1, t2;
        int m=(l+r)>>1;
        if(ql<=m){
            t1= query(2*u,ql,qr);
        }
        if(m<qr){
            t2= query(2*u+1,ql,qr);
        }
        combine(res, t1, t2);
        return res;
    }

    //区域更新[ql,qr]+c
    void update(int u, int ql, int qr, int c){
        int l=val[u].l;
        int r=val[u].r;
        if(ql<=l && r<=qr){
            eval(val[u], c);
            return;
        }
        pushdown(u);
        int m=(l+r)>>1;
        if(ql<=m){
            update(2*u,ql,qr,c);
        }
        if(m<qr){
            update(2*u+1,ql,qr,c);
        }
        combine(val[u], val[2*u], val[2*u+1]);
    }

    //单点设置
    void set(int u, int pos, T c){
        int l=val[u].l;
        int r=val[u].r;
        if(l==r){
            evalSet(val[u], c);
            return;
        }
        pushdown(u);
        int m=(l+r)>>1;
        if(pos<=m){
            set(2*u,pos,c);
        }else{
            set(2*u+1,pos,c);
        }
        combine(val[u], val[2*u], val[2*u+1]);
    }
};

void solve() {
    LL n,q;
    cin>>n>>q;
    vector<LL> a(n);
    for (LL i=1; i<=n; i++) {
        cin>>a[i-1];
    }
    SEGMENTTREE<LL> tr(a);
    SEGNODE<LL> res=tr.query(1,1,n);
    cout<<res.max_sum<<"\n";
    for (int i=1; i<=q; i++) {
        int pos;
        LL val;
        cin>>pos>>val;

        pos++;
        tr.set(1,pos,val);

        res=tr.query(1,1,n);
        cout<<res.max_sum<<"\n";
    }
}

int main() {
#if 1
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie (0);
#endif

    //freopen("00.in", "r", stdin);
    //freopen("00.out", "w", stdout);

    int T=1;
    //cin>>T;
    for (int i=1; i<=T; i++) {
        //cout<<i<<"\n";
        solve();
    }
    return 0;
}
