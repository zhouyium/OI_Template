/*
 * https://acm.hdu.edu.cn/showproblem.php?pid=4280
 * http://47.110.135.197/problem.php?id=10340
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

struct MF_GRAPH {
public:
    MF_GRAPH() : _n(0) {}
    explicit MF_GRAPH(int n) : _n(n), _adj(n) {}

    /*
     * type表示边的类型
     * 0表示有向图，1表示无向图
     */
    int add(int from, int to, long long cap, int type=0) {
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
        long long cap, flow;
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
    void change_edge(int i, long long new_cap, long long new_flow) {
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
    long long flow(int s, int t) {
        return flow(s, t, std::numeric_limits<long long>::max());
    }
    long long flow(int s, int t, long long flow_limit) {
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
        auto dfs = [&](auto self, int v, long long up) {
            if (v == s) return up;
            long long res = 0;
            int level_v = level[v];
            for (int i = iter[v]; i < int(_adj[v].size()); i++) {
                _EDGE e = _adj[v][i];
                if (level_v <= level[e.to] || _adj[e.to][e.rev].cap == 0){
                    continue;
                }
                long long d = self(self, e.to, std::min(up - res, _adj[e.to][e.rev].cap));
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

        long long flow = 0;
        while (flow < flow_limit) {
            bfs();
            if (level[t] == -1) {
                break;
            }

            iter.assign(_n+1,0);
            long long f = dfs(dfs, t, flow_limit - flow);
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
        long long cap;
    };
    std::vector<std::vector<_EDGE>> _adj;
};

/*
 * 使用方法
 * 1. 初始化
 *   MF_GRAPH flow(n+2); //注意，我们是从下标 1 开始
 * 2. 加边
 *   flow.add(x,y,f);//x->y f
 * 3. 计算最大流
 *   flow.flow(1,n);
 */

void solve(){
    //初始化
    int n,m;
    cin>>n>>m;
    //起点是最左边的点，终点是最右边的点
    int scr, dst;
    int le=2e9, ri=-2e9;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        if(x<le){
            le=x;
            scr=i;
        }
        if(x>ri){
            ri=x;
            dst=i;
        }
    }
    //初始化
    MF_GRAPH flow(n+2);
    for(int i=1;i<=m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        //特别注意：本地是无向图，所以add的时候要注意
        //也可以修改add函数。加上反向边的时候，cap不为零
        //改add函数在HDU上是5896ms。加两次边是8611ms
        flow.add(a,b,c);
        flow.add(b,a,c);
    }
    cout<<flow.flow(scr,dst)<<"\n";
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T=1;
    cin>>T;
    for(int i=1;i<=T;i++){
        //cout<<"Case "<<i<<": ";
        solve();
    }
    return 0;
}