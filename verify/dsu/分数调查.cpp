/***
 * 分数调查
http://47.110.135.197/problem.php?id=6688
***/
#include <bits/stdc++.h>
using namespace std;
using LL=long long;
using PLL=pair<LL,LL>;

//并查集节点定义
template<typename T=long long>
struct DSUNODE{
    int fa;//表示编号为i的节点父亲是谁。-1表示根节点
    T w;//节点到父亲的权值
    //下面的内容根据题目添加
};
//并查集模板
template<typename T=long long>
struct DSU{
    //
private:
    std::vector<DSUNODE<T>> val;

public:
    DSU(int n=5e5){
        //初始化数据
        for(int i=0;i<=n;i++){
            val.push_back({-1,0});
        }
    }

    //找x的父亲
    int find(int x){
        if(val[x].fa<0){
            return x;
        }
        int t=val[x].fa;
        val[x].fa=find(val[x].fa);
        val[x].w+=val[t].w;//val[x].w原来是与t的相对距离，现在是相对root的距离
        return val[x].fa;
    }

    //x的父亲是y
    bool join(int x,int y,T c=0){
        int fx=find(x);
        int fy=find(y);
        if(fx==fy){
            return false;
        }
        val[fy].fa+=val[fx].fa;//合并集合大小
        val[fx].fa=fy;
        //权值变化根据题目来定
        val[fx].w=val[y].w-val[x].w+c;
        return true;
    }

    void add(int x, T c){
        int fx=find(x);
        val[fx].w+=c;
    }

    int size(int x){
        int fx=find(x);
        return -val[fx].fa;
    }

    bool same(int x,int y){
        int fx=find(x);
        int fy=find(y);
        return fx==fy;
    }

    DSUNODE<T> node(int x){
        return val[x];
    }
};


void solve(){
    int n,m,q;
    cin>>n>>m>>q;
    DSU<> dsu(n+1);

    for(int i=1;i<=m;i++){
        int x,y,s;
        cin>>x>>y>>s;
        dsu.join(x,y,s);
    }
    for(int i=1;i<=q;i++){
        int x,y;
        cin>>x>>y;
        if(!dsu.same(x,y)){
            cout<<"-1\n";
        }else{
            DSUNODE<> ret1=dsu.node(x);
            DSUNODE<> ret2=dsu.node(y);
            cout<<ret1.w-ret2.w<<"\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    //freopen("censor.in","r",stdin);
    //freopen("censor.out","w",stdout);
    int T=1;
    //cin>>T;
    while (T--){
        solve();
    }

    return 0;
}