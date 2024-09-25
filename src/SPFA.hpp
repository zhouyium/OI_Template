#pragma once

#include<vector>
#include<utility>

/**
 * 单源最短路径，含负权边
 * 时间复杂度 O(|V||E|)
 * |V|是图中顶点的数量，|E|是边的数量。
 */
//
std::vector<std::vector<std::pair<int, int>>> adj;//邻接表存图
std::vector<bool> vis;//节点是否在队列里
std::vector<int> dis;//节点到起点距离
std::vector<int> cnt;//从起点到编号为 i 的节点包含多少边

//节点数量，节点编号 1~n
void init(int n){
    adj.assign(n+1,vector<pair<int,int>>());
    vis.assign(n+1, false);
    dis.assign(n+1, INF);
    cnt.assign(n+1, 0);
}

/**
 *
 * @param st 起点
 */
bool spfa(int st){
    //初始化
    vis.assign(n+1, false);
    dis.assign(n+1, INF);
    cnt.assign(n+1, 0);

    std::priority_queue<int,
            std::vector<int>,
            greater<int>> que;
    vis[st]=true;//st节点已经在队列
    dis[st]=0;
    que.push(st);
    while(que.size()){
        int u=que.top();que.pop();
        vis[u]=false;//u不在队列

        for(const auto &node : adj[u]){
            int v=node.first;
            int w=node.second;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;

                //负环判断
                cnt[v]=cnt[u]+1;
                if(cnt[v]>=n){
                    return true;
                }

                if(vis[v]==false){
                    //v不在队列
                    vis[v]=true;
                    que.push(v);
                }
            }
        }
    }
    return false;
}