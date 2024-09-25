#pragma once

#include<vector>
#include<utility>

/**
 * 单源最短路径，边权非负
 * 时间复杂度 O((|V|+|E|)log|V|)
 * |V|是图中顶点的数量，|E|是边的数量。
 */
//adj.assign(n+1,vector<pair<int,int>>());
std::vector<std::vector<std::pair<int, int>>> adj;//邻接表存图
std::vector<bool> vis;//节点可见性控制
std::vector<int> dis;//节点到起点距离

//节点数量，节点编号 1~n
void init(int n){
    adj.assign(n+1,vector<pair<int,int>>());
    vis.assign(n+1, false);
    dis.assign(n+1, INF);
}

/**
 *
 * @param st 起点
 */
void dij(int st){
    //初始化
    vis.assign(n+1, false);
    dis.assign(n+1, INF);

    std::priority_queue<std::pair<int, int>,
            std::vector<std::pair<int, int>>,
            greater<std::pair<int, int>>> que;
    dis[st]=0;
    que.push({0,st});
    while(que.size()){
        auto t=que.top();que.pop();

        int u=t.second;
        if(vis[u]){
            continue;
        }
        vis[u]=true;

        for(const auto &node : adj[u]){
            int v=node.first;
            int w=node.second;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                que.push({dis[v],v});
            }
        }
    }
}
