#pragma once

/**
 * @brief 根据给定的有向图邻接表 adj，计算出该图的强连通分量。
 * @version 1.0.0
 * @date 2024-9-18
 * @author YiZHOU
 * @copydetails 本模板参考金牌选手 JiangLY 的模板
 * 下面的链接是 JiangLY 使用提交
 * https://codeforces.com/contest/1835/submission/210147209
 */
struct SCC {
    //下面是 SCC 的输入
    int n;
    std::vector<std::vector<int>> adj;//< 邻接表
    //上面是 SCC 的输入
    std::vector<int> stk;//使用队列模拟堆栈
    std::vector<int> dfn, low;
    int cur;
    //下面是 SCC 的输出
    std::vector<int> scc;//< 表示编号为 i 的节点属于 SCC 编号为 scc[i]
    int cnt;//< 图中 SCC 的总数量，可用 SCC 编号为 0,1,...,cnt-1
    //上面是 SCC 的输出
    /*这个部分增加额外数据*/
    /*这个部分增加额外数据*/

    SCC() {}
    SCC(int n) {
        init(n);
    }

    void init(int n) {
        this->n = n;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        scc.assign(n, -1);
        stk.clear();
        cur = cnt = 0;
        /*这个部分增加额外数据初始化*/
        /*这个部分增加额外数据初始化*/
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void tarjan(int x) {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);

        for (auto y : adj[x]) {
            if (dfn[y] == -1) {
                tarjan(y);
                low[x] = std::min(low[x], low[y]);
            } else if (scc[y] == -1) {
                low[x] = std::min(low[x], dfn[y]);
            }
        }

        if (dfn[x] == low[x]) {
            int y;
            do {
                y = stk.back();
                stk.pop_back();
                scc[y] = cnt;
                /*这个部分增加额外数据维护*/
                /*这个部分增加额外数据维护*/
            } while (y != x);
            cnt++;
        }
    }

    std::vector<int> work() {
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                tarjan(i);
            }
        }
        return scc;
    }

    /*这个部分增加额外数据维护*/
    /*这个部分增加额外数据维护*/
};
