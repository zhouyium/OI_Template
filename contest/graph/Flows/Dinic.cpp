namespace DINIC {
/*
 * Dinic算法实现。
 * 来自AtCoder Library
 * https://github.com/atcoder/ac-library/blob/master/atcoder/maxflow.hpp
 * 时间复杂度 O(n^2*m) n是节点数，m是边数
 */
#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
#include <vector>

    using CAP = long long;
    const CAP INF = std::numeric_limits<CAP>::max();

    int _n;//图上节点数量
    int _m;//图上边数量
    //保存具体的边集
    std::vector<std::pair<int, int>> _pos;
    //保存图
    struct _EDGE {
        int to;//v点
        int rev;//下一个边
        CAP cap;
    };
    std::vector<std::vector<_EDGE>> G;

    void init(int n, int m) {
        _n=n;
        _m=m;
        G.assign(_n,std::vector<_EDGE>());
        _pos.clear();
    }

    int add(int from, int to, CAP cap, bool isDirected=true) {
        assert(0<=from && from<_n);
        assert(0<=to && to<_n);
        assert(0<=cap);
        int m = _pos.size();
        _pos.push_back({from, G[from].size()});
        int from_id = G[from].size();
        int to_id = G[to].size();
        if (from == to) {
            to_id++;
        }
        G[from].push_back(_EDGE{to, to_id, cap});
        G[to].push_back(_EDGE{from, from_id, isDirected ? 0 : cap});
        return m;
    }

    /*
     * returns the current internal state of the edges.
     */
    struct EDGE {
        int from, to;
        CAP cap, flow;
    };
    /*
     * returns the current internal state of the edges.
     */
    EDGE get_edge(int i) {
        int m = _pos.size();
        assert(0 <= i && i < m);
        auto _e = G[_pos[i].first][_pos[i].second];
        auto _re = G[_e.to][_e.rev];
        return EDGE{_pos[i].first, _e.to, _e.cap + _re.cap, _re.cap};
    }
    std::vector<EDGE> edges() {
        int m = _pos.size();
        std::vector<EDGE> result;
        for (int i = 0; i < m; i++) {
            result.push_back(get_edge(i));
        }
        return result;
    }
    void change_edge(int i, CAP new_cap, CAP new_flow) {
        int m = _pos.size();
        assert(0 <= i && i < m);
        assert(0 <= new_flow && new_flow <= new_cap);
        auto& _e = G[_pos[i].first][_pos[i].second];
        auto& _re = G[_e.to][_e.rev];
        _e.cap = new_cap - new_flow;
        _re.cap = new_flow;
    }

    /*
     * 求解从 s 到 t 的最大流
     * 时间复杂度O(n^2 m)
     */
    CAP flow(int s, int t, CAP flow_limit) {
        assert(0 <= s && s < _n);
        assert(0 <= t && t < _n);
        assert(s != t);

        std::vector<int> level(_n);
        std::vector<int> iter(_n);
        ////通过bfs计算从源点出发的距离标号
        auto bfs = [&]() {
            level.assign(_n+1,-1);
            level[s] = 0;

            std::queue<int> que;
            que.push(s);
            while (!que.empty()) {
                int v = que.front();
                que.pop();
                for (auto e : G[v]) {
                    if (e.cap == 0 || level[e.to] >= 0){
                        continue;
                    }
                    level[e.to] = level[v] + 1;
                    if (e.to == t) {
                        return;
                    }
                    que.push(e.to);
                }
            }
        };
        //通过dfs寻找增广路
        auto dfs = [&](auto self, int v, CAP up) {
            if (v == s) return up;
            CAP res = 0;
            int level_v = level[v];
            for (int i = iter[v]; i < G[v].size(); i++) {
                _EDGE e = G[v][i];
                if (level_v <= level[e.to] || G[e.to][e.rev].cap == 0){
                    continue;
                }
                CAP d = self(self, e.to, std::min(up - res, G[e.to][e.rev].cap));
                if (d <= 0) {
                    continue;
                }
                G[v][i].cap += d;
                G[e.to][e.rev].cap -= d;
                res += d;
                if (res == up) {
                    return res;
                }
            }
            level[v] = _n;
            return res;
        };

        CAP flow = 0;
        while (flow < flow_limit) {
            bfs();
            if (level[t] == -1) {
                break;
            }

            iter.assign(_n+1,0);
            CAP f = dfs(dfs, t, flow_limit - flow);
            if (!f) break;
            flow += f;
        }
        return flow;
    }
    CAP flow(int s, int t) {
        return flow(s, t, INF);
    }

    /*
     * It returns a vector of length n, such that the i-th element is true if and only if
     * there is a directed path from s to i in the residual network. The returned vector
     * corresponds to a s-t minimum cut after calling flow(s, t) exactly once without flow_limit.
     * O(n+m)
     */
    std::vector<bool> min_cut(int s) {
        std::vector<bool> visited(_n);
        std::queue<int> que;
        que.push(s);
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            visited[p] = true;
            for (auto e : G[p]) {
                if (e.cap && !visited[e.to]) {
                    visited[e.to] = true;
                    que.push(e.to);
                }
            }
        }
        return visited;
    }
}

/*
 * 初始化    DINIC::init(n+2, m+2);
 * 加有向边  DINIC::add(u, v, flow);
 * 加无向边  DINIC::add(u, v, flow, false);
 * 求解     DINIC::flow(src,dst);
 */