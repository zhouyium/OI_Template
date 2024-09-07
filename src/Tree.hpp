#pragma once

#include <vector>

namespace lz {

struct TREE {
    int n;
    std::vector<int> siz;//siz[i]表示以 i 为根节点的树节点数量
    std::vector<int> top;//重链头节点。top[i]表示编号为 i 的节点，头节点是 top[i]。
    std::vector<int> dep;//dep[i]表示以 i 为根节点的树节点深度。根节点深度为 0
    std::vector<int> parent;//parent[i]表示节点 i 的父亲
    std::vector<int> son;//重儿子。son[i]表示编号为 i 的节点，重儿子节点是 son[i]。
    std::vector<int> in;//入栈顺序
    std::vector<int> out;//出栈顺序
    std::vector<std::vector<int>> adj;
    //树初始化
    TREE(int n) : n(n+1), siz(n+1), top(n+1), dep(n+1), parent(n+1, -1), son(n+1), in(n+1), out(n+1), adj(n+1) {}
    //增加一条u->v的无向边
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    //初始化
    void init(int root = 1) {
        top[root] = root;
        dfs1(root);
        dfs2(root,root);
    }
    //u 当前节点
    //计算 siz, dep, parent, son
    void dfs1(int u) {
        siz[u] = 1;
        dep[u] = dep[parent[u]] + 1;
        for (auto v : adj[u]) {
            if(v==parent[u]){
                continue;
            }
            parent[v] = u;//更新父亲
            dfs1(v);
            siz[u] += siz[v];//更新子树大小
            if (siz[v] > siz[son[u]]) {
                son[u] = v;//更新重儿子
            }
        }
    }
    //u:当前节点
    //h:节点u的重链头节点
    //计算 top, in, out
    int cur = 0;//时间戳
    void dfs2(int u, int h) {
        in[u] = cur++;
        top[u] = h;
        if(son[u]==0){
            //叶子节点
            return;
        }
        //遍历重儿子
        dfs2(son[u],h);
        //遍历轻儿子
        for (auto v : adj[u]) {
            //  回边             重儿子
            if(v==parent[u] || v==son[u]){
                continue;
            }
            //v是轻儿子
            dfs2(v,v);
        }
        out[u] = cur;
    }
    //Least Common Ancestors
    //重链剖分求LCA
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            //u,v不是同一条重链
            //比较u,v深度
            if (dep[top[u]] < dep[top[v]]) {
                std::swap(u,v);
            }
            u = parent[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
};

}
