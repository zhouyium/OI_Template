/*
 * https://atcoder.jp/contests/abc326/tasks/abc326_g
 * http://47.110.135.197/problem.php?id=10361
 */
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
/*
 *最大流 MaxFlow
 * 修改自AtCoder Library
 * https://github.com/atcoder/ac-library/blob/master/atcoder/maxflow.hpp
 */
#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
#include <vector>

template <class CAP>struct MF_GRAPH {
public:
    MF_GRAPH() : _n(0) {}
    explicit MF_GRAPH(int n) : _n(n), _adj(n) {}

    int add(int from, int to, CAP cap) {
        assert(0<=from && from<_n);
        assert(0<=to && to<_n);
        assert(0<=cap);
        int m = int(_pos.size());
        _pos.push_back({from, int(_adj[from].size())});
        int from_id = int(_adj[from].size());
        int to_id = int(_adj[to].size());
        if (from == to) {
            to_id++;
        }
        _adj[from].push_back(_EDGE{to, to_id, cap});
        _adj[to].push_back(_EDGE{from, from_id, 0});
        return m;
    }

    /*
     * returns the current internal state of the edges.
     */
    struct EDGE {
        int from, to;
        CAP cap, flow;
    };
    EDGE get_edge(int i) {
        int m = int(_pos.size());
        assert(0 <= i && i < m);
        auto _e = _adj[_pos[i].first][_pos[i].second];
        auto _re = _adj[_e.to][_e.rev];
        return EDGE{_pos[i].first, _e.to, _e.cap + _re.cap, _re.cap};
    }
    std::vector<EDGE> edges() {
        int m = int(_pos.size());
        std::vector<EDGE> result;
        for (int i = 0; i < m; i++) {
            result.push_back(get_edge(i));
        }
        return result;
    }
    void change_edge(int i, CAP new_cap, CAP new_flow) {
        int m = int(_pos.size());
        assert(0 <= i && i < m);
        assert(0 <= new_flow && new_flow <= new_cap);
        auto& _e = _adj[_pos[i].first][_pos[i].second];
        auto& _re = _adj[_e.to][_e.rev];
        _e.cap = new_cap - new_flow;
        _re.cap = new_flow;
    }

    /*
     * 求解从 s 到 t 的最大流
     * 时间复杂度O(n^2 m)
     */
    CAP flow(int s, int t) {
        return flow(s, t, std::numeric_limits<long long>::max());
    }
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
                for (auto e : _adj[v]) {
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
            for (int i = iter[v]; i < int(_adj[v].size()); i++) {
                _EDGE e = _adj[v][i];
                if (level_v <= level[e.to] || _adj[e.to][e.rev].cap == 0){
                    continue;
                }
                CAP d = self(self, e.to, std::min(up - res, _adj[e.to][e.rev].cap));
                if (d <= 0) {
                    continue;
                }
                _adj[v][i].cap += d;
                _adj[e.to][e.rev].cap -= d;
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
            for (auto e : _adj[p]) {
                if (e.cap && !visited[e.to]) {
                    visited[e.to] = true;
                    que.push(e.to);
                }
            }
        }
        return visited;
    }

private:
    int _n;//图上节点数量
    //保存具体的边集
    std::vector<std::pair<int, int>> _pos;
    //保存图
    struct _EDGE {
        int to;//v点
        int rev;//下一个边
        CAP cap;
    };
    std::vector<std::vector<_EDGE>> _adj;
};

constexpr int N = 1e2 + 5;
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

void solve(){
    int n,m;
    cin>>n>>m;
    MF_GRAPH<long long> gr(5*n+m+2);

    vector<int> a(m+2);
    for(int i=1;i<=n;i++){
        int c;
        cin>>c;
        gr.add(0,i,0);
        for(int j=1;j<=4;j++){
            gr.add(i+n*(j-1),i+n*j,1ll*c*j);
            gr.add(i+n*j,i+n*(j-1),9e18);
        }
        gr.add(i+4*n,5*n+m+1,c*4);
    }

    LL sum=0;
    for(int i=1;i<=m;i++){
        cin>>a[i];
        sum+=a[i];
    }
    for(int i=1;i<=m;i++){
        gr.add(0,5*n+i,a[i]);
        for(int j=1;j<=n;j++){
            int l;
            cin>>l;
            for(int k=0;k<l-1;k++){
                gr.add(5*n+i,j+n*k,9e18);
            }
        }
    }

    long long ret=gr.flow(0,5*n+m+1);
    cout<<max(0ll,sum-ret)<<"\n";
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T=1;
    //cin>>T;
    for(int i=1;i<=T;i++){
        //cout<<"Case "<<i<<": ";
        solve();
    }
    return 0;
}