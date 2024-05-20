/***
 * [NOI2001] 食物链
https://www.luogu.com.cn/problem/P2024
http://47.110.135.197/problem.php?id=4386
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
        int nxt=find(val[x].fa);
        //维护到父亲的权值，每题不一样
        val[x].w+=val[val[x].fa].w;//val[x].w原来是与t的相对距离，现在是相对root的距离
        val[x].fa=nxt;
        return val[x].fa;
    }

    //x的父亲是y
    bool join(int x,int y,T c=0){
        int fx=find(x);
        int fy=find(y);
        if(fx==fy){
            return false;
        }
        //按秩合并
        //if(-val[fx].fa>-val[fy].fa){
        //    swap(fx,fy);
        //}
        val[fy].fa+=val[fx].fa;//合并集合大小
        val[fx].fa=fy;
        //权值变化根据题目来定
        val[fx].w=((val[y].w-val[x].w)%3+c)%3;
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
    cin>>n>>m;
    DSU<> dsu(n+1);
    int ans=0;
    for(int i=1;i<=m;i++){
        int op,x,y;
        cin>>op>>x>>y;
        if(x>n||y>n){
            ans++;
            continue;
        }
        if(op==1){
            //判断x，y是否为同类（d[x]=d[y]，在%3意义下）
            if(dsu.same(x,y)){
                DSUNODE<> ret1=dsu.node(x);
                DSUNODE<> ret2=dsu.node(y);
                if(((ret1.w-ret2.w)%3+3)%3!=0){
                    ans++;
                }
            }else{
                dsu.join(x,y);
            }
        }else{
            // 判断x是否捕食y（d[x]-d[y]=2，在%3意义下）
            if(dsu.same(x,y)){
                DSUNODE<> ret1=dsu.node(x);
                DSUNODE<> ret2=dsu.node(y);
                if(((ret1.w-ret2.w)%3+3)%3!=2){
                    ans++;
                }
            }else{
                dsu.join(x,y,2);
            }
        }
    }
    cout<<ans<<"\n";
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