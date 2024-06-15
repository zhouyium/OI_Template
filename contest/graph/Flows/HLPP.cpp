namespace HLPP {
    /*
     * HLPP(Highest Label Preflow Push) 最高标签预流推进算法
     * 时间复杂度: O(n^2\times \sqrt(m))
     */
#include <vector>
#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
    //这里的N根据题目需求改动
    //const int N = 1200 + 10;
    using CAP = long long;
    const CAP INF = std::numeric_limits<CAP>::max();

    struct _EDGE {
        int to, idx;
        CAP flow;
        bool origin;
        _EDGE(int _to = 0, int _idx = 0, CAP fl = 0, bool ori = 1) : to(_to), idx(_idx), flow(fl), origin(ori) {}
    };

    int n, m;
    int high_label, relabel_cnt;
    std::vector<std::vector<_EDGE>> g;
    std::vector<std::vector<int>> Q;
    std::vector<CAP> X;
    std::vector<int> H;
    std::vector<int> P;
    //CAP X[N];
    //int H[N], P[N];

    void init(int _n, int _m) {
        n=_n;
        m=_m;
        high_label=relabel_cnt=0;
        g.assign(_n,std::vector<_EDGE>());
        Q.assign(_n,std::vector<int>());
        X.assign(_n,0);
        H.assign(_n,0);
        P.assign(_n,0);
    }

    void add(int u, int v, CAP flow, bool directed = true) {
        int p = g[u].size(), q = g[v].size();
        g[u].emplace_back(_EDGE(v, q, flow, 1));
        g[v].emplace_back(_EDGE(u, p, directed ? 0 : flow, 0));
    }

    void push(int u) {
        Q[H[u]].emplace_back(u);
        high_label = max(high_label, H[u]);
    }

    void relabel(int t) {
        relabel_cnt = 0;

        for (int i = 0; i <= high_label; ++i){
            Q[i].clear();
        }

        //memset(H, 0x7f, n << 2);
        for(int i=0;i<n;i++){
            H[i]=INT_MAX;
        }
        std::queue<int> q;
        q.push(t), H[t] = 0;

        while (q.size()) {
            int u = q.front();
            q.pop();
            int h = H[u] + 1;

            for (auto &x : g[u]) // [v, idx, flow, origin]
                if (g[x.to][x.idx].flow && h < H[x.to]) {
                    q.push(x.to), H[x.to] = h;

                    if (X[x.to]){
                        push(x.to);
                    }
                }
        }
    }

    void discharge(int u) {
        CAP &tmp_flow = X[u];
        int h = n;

        for (int &p = P[u], sz = g[u].size(); sz--; --(p ? p : p = g[u].size())) {
            auto &x = g[u][p]; // [v, idx, flow, origin]

            if (!x.flow){
                continue;
            }

            if (H[u] < H[x.to] + 1) {
                h = min(h, H[x.to] + 1);
                continue;
            }

            const CAP f = min(x.flow, tmp_flow);
            x.flow -= f, tmp_flow -= f;

            if (!X[x.to]){
                push(x.to);
            }

            X[x.to] += f, g[x.to][x.idx].flow += f;

            if (!tmp_flow){
                return;
            }
        }

        ++relabel_cnt, H[u] = h;

        if ((H[u] ^ n) && X[u]){
            push(u);
        }
    }

    CAP solve(int s, int t) {
        const long long k = ((32 - __builtin_clz(m + 1)) * n) >> 1;
        relabel(t);
        X[s] = INF;X[t] = -INF;
        push(s);

        for (; high_label >= 0; --high_label) {
            while (Q[high_label].size()) {
                int u = Q[high_label].back();
                Q[high_label].pop_back();

                if (H[u] == high_label) {
                    discharge(u);

                    if (relabel_cnt == k){
                        relabel(t);
                    }
                }
            }
        }

        return X[t] + INF;
    }
}

/*
 * 初始化    HLPP::init(n+2, m+2);
 * 加有向边  HLPP::add(u, v, flow);
 * 加无向边  HLPP::add(u, v, flow, false);
 * 求解     HLPP::solve(src,dst);
 */