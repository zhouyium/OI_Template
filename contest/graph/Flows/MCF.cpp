namespace MinCostFlow{
    /*
     * 最小费用流
     * 基于 Dinic 算法的实现
     * https://oi-wiki.org/graph/flow/min-cost/
     */
#include <cassert>
#include <limits>
#include <queue>
    using CAP = long long;
    const CAP INF = std::numeric_limits<CAP>::max();
    //根据每题修改节点和边的数量
    const int N=5e3+10;
    const int M=1e5+10;

    int n;//节点数量
    int m;//边数量
    int idx;//
    int h[N];//头结点
    int cur[N];//当前头结点
    int e[M];
    int ne[M];
    CAP dis[N];//距离
    CAP cap[M];
    CAP cost[M];
    bool vis[N];
    CAP ret;//最小费用

    //初始化
    void init(int _n,int _m){
        n=_n;
        m=_m;
        idx=0;
        ret=0;
        for(int i=0;i<=n;i++){
            h[i]=-1;
        }
    }

    void add(int u,int v,int w,int c){
        e[idx]=v;
        ne[idx]=h[u];
        cap[idx]=w;
        cost[idx]=c;
        h[u]=idx++;
    }

    void add_edge(int u,int v,int w,int c,bool isDirected=true){
        add(u,v,w,c);
        add(v,u,0,-c);
    }

    bool spfa(int src,int dst){
        //初始化距离
        for(int i=0;i<=n;i++){
            dis[i]=INF;
            cur[i]=h[i];
            vis[i]=false;
        }

        std::queue<int> que;
        que.push(src);
        dis[src]=0;
        vis[src]=true;
        while(que.size()){
            int u=que.front();
            que.pop();
            vis[u]=false;

            for(int i=h[u];i!=-1;i=ne[i]){
                int v=e[i];
                if(cap[i] && dis[v]>dis[u]+cost[i]){
                    dis[v]=dis[u]+cost[i];//松弛
                    if(vis[v]==false){
                        //不在队列
                        que.push(v);
                        vis[v]=true;
                    }
                }
            }
        }
        return dis[dst]!=INF;
    }

    CAP dfs(int u,int dst,CAP flow){
        if(dst==u){
            return flow;
        }
        vis[u]=true;
        CAP ans=0;
        for(int i=cur[u]; i!=-1 && ans<flow; i=ne[i]){
            int v=e[i];
            if(vis[v]==false && cap[i] && dis[v]==dis[u]+cost[i]){
                CAP x=dfs(v,dst,std::min(cap[i],flow-ans));
                if(x){
                    ret+=x*cost[i];
                    cap[i]-=x;
                    cap[i^1]+=x;
                    ans+=x;
                }
            }
        }
        vis[u]=false;
        return ans;
    }

    /*
     * 第一个数值：该网络的最大流 F(G)
     * 第二个数值：该网络的最小费用 C(G)
     */
    pair<CAP,CAP> mcmf(int src,int dst){
        CAP ans=0;
        while(spfa(src,dst)){
            CAP x;
            while(x=dfs(src,dst,INF)){
                ans+=x;
            }
        }
        return make_pair(ans,ret);
    }
}

/*
 * 使用方法
 * 初始化       MinCostFlow::init(n+2, m+2);
 * 加边        MinCostFlow::add_edge(u,v,w,c);
 * 求解        pair<long long,long long> ret=MinCostFlow::mcmf(src,dst);
 * 模板题  https://www.luogu.com.cn/problem/P3381
 */