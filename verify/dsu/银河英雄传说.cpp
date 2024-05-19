/***
 * 银河英雄传说
https://www.luogu.com.cn/problem/P1196
http://47.110.135.197/problem.php?id=6691
***/
#include <bits/stdc++.h>
using namespace std;
using LL=long long;
using PLL=pair<LL,LL>;

//并查集节点定义
template<typename T=long long>
struct DSUNODE{
    int fa;//表示编号为i的节点父亲是谁。-1表示根节点
    //下面的内容根据题目添加
    T dis;//表示飞船与其所在列队头的距离
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
        val[x].dis+=val[t].dis;//val[x].w原来是与t的相对距离，现在是相对root的距离
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

        //处理权值变化根据题目来定
        val[fx].dis+=-val[fy].fa;

        //合并集合
        val[fy].fa+=val[fx].fa;//合并集合大小
        val[fx].fa=fy;
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
    cin>>m;
    DSU<> dsu(3e4+1);
    for(int i=1;i<=m;i++){
        char op;
        int x,y;
        cin>>op>>x>>y;
        if(op=='M'){
            dsu.join(x,y);
        }else if(op=='C'){
            if(dsu.same(x,y)==false){
                //x和y的祖先不相同，则不在同一列
                cout<<"-1\n";
            }else{
                DSUNODE<> ret1=dsu.node(x);
                DSUNODE<> ret2=dsu.node(y);
                cout<<abs(ret1.dis-ret2.dis)-1<<"\n";
            }
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