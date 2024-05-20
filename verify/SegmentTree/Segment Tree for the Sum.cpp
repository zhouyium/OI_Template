/*
 * https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/A
 * http://47.110.135.197/problem.php?id=5645
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
    T sum;//和
    //缺省构造函数
    SEGNODE(){
        l=r=0;
        add=sum=0;
    }
};
template<typename T=long long>
class SEGMENTTREE{
private:
    std::vector<SEGNODE<T>> val;//保存数据

private:
    //将左右儿子合成一个新节点
    void combine(SEGNODE<T> &t, const SEGNODE<T> &t1, const SEGNODE<T> &t2){
        t.sum=t1.sum+t2.sum;
        t.l  =min(t1.l, t2.l);
        t.r  =max(t1.r, t2.r);
    }

    void eval(SEGNODE<T> &t, T add){
        t.sum = t.sum+(t.r-t.l+1)*add;
        if(t.l==t.r){
            //leaf
            t.add=0;
        }else{
            t.add+=add;//加上懒标记
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

    //[ql,qr]+c
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
};

void solve() {
    LL n,q;
    cin>>n>>q;
    vector<LL> a(n);
    for (LL i=1; i<=n; i++) {
        cin>>a[i-1];
    }
    SEGMENTTREE<LL> tr(a);
    for (LL i=1; i<=q; i++) {
        LL op,ql,qr;
        cin>>op>>ql>>qr;

        if (op==1) {
            ql++;
            SEGNODE<LL> res=tr.query(1,ql,ql);
            tr.update(1,ql,ql,qr-res.sum);
        } else if (op==2){
            ql++;
            SEGNODE<LL> res=tr.query(1,ql,qr);
            cout<<res.sum<<"\n";
        }
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
